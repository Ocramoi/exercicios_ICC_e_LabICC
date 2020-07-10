#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct // estrutura do objeto 
{
    char *lexical;
    int num;
} OBJ;

#define STR_BUFFER 2048 // buffer do realloc de string

char *leFrase(FILE* entrada) { // função que lê string com tratamento
    char *retorno = NULL; // inicializa o ponteiro da frase lida
    int cont = 0; // inicializa a varável que auxiliará o tratamento de tamanho

    do {
        if (cont % STR_BUFFER == 0) { // conferência do tamanho como próximo múltiplo do buffer
            retorno = (char* ) realloc(retorno, ((cont/STR_BUFFER + 1) * STR_BUFFER) * sizeof(char)); // aumenta o tamanho da string em função do buffer caso tenha ultrapassado um novo múltiplo, diminuindo o gasto computacional com realocação
        }
        retorno[cont] = fgetc(entrada); // lê novo caracter
        cont++; // atualiza o tamanho da string
    } while (retorno[cont-1] != '\n' && retorno[cont-1] != EOF); // repete até o final da leitura de string

    if (cont >= 2 && retorno[cont - 2] == '\r') { // confere pelo caracter de formatação '/r'
        retorno[cont - 2] = '\0'; // substitui o caracter por fim de string
        retorno = (char* ) realloc(retorno, (cont-1) * sizeof(char)); // diminui o tamanho da string em 1 caracter
    }
    else {
        retorno[cont-1] = '\0'; // formata a string com o caracter de final de string
        retorno = (char* ) realloc(retorno, cont * sizeof(char)); // realoca o ponteiro da string para seu tamanho desconsiderando o buffer
    }
    return retorno; // retorna a string lida
}

OBJ *retornaObj(char* frase) // recebe a frase lida e retorna o objeto com parte textual e numérica
{
    OBJ* retorno = malloc(sizeof(OBJ)); // ponteiro do objeto
    char *textual = NULL, // ponteiro da parte textual da frase
         *num = NULL; // ponteiro da parte numérica da frase
    char flag = 1; // flag da mudnça de parte
    int cont; // variável do primeiro caracter da parte númerica da frase

    for (int i = 0; i < strlen(frase); ++i) { // loop pelos caracteres
        if(((frase[i] >= 48 && frase[i] <= 57) ||
            (frase[i] == '-' && (frase[i+1] >= 48 && frase[i+1] <= 57)))
            && flag == 1) { // indica o começo da parte númerica naquele caracter
            flag = 0; // modifica a flag
            cont = i; // indica o início da parte numérica naquele caracter
            textual[i-1] = '\0'; // acrescenta o fim de string da parte textual
        }

        if (flag) // se não chegado o fim da parte textual
        {
            // atualiza o tamanho da parte textual com o novo caracter
            textual = realloc(textual, (i + 2) * sizeof(char));
            textual[i] = frase[i];
        } else {
            // aloca a parte numérica da frase
            num = realloc(num, ((i - cont) + 2) * sizeof(char));
            num[i - cont] = frase[i];
        }
    }

    retorno->lexical = textual; // configura a parte textual do objeto
    retorno->num = atoi(num); // configura a parte numérico do objeto

    free(num); // libera o ponteiro da versão textual da parte numérica

    return retorno; // retorna o objeto configurado
}

char toLowerCase(char c) // retorna o caracter lowercase caso seja uppercase
{
    if(c >= 65 && c <= 90)
        return c + 32;
    else
        return c;
}

char conferencia(OBJ* a, OBJ* b, int op) // função de conferencia para o select sort com ambas as opções
{
    if(op == 1)
    {
        int maximo = (strlen(a->lexical) < strlen(b->lexical)) ? strlen(a->lexical) : strlen(b->lexical); // menor tamanho de string entre as duas para loop
        for (int i = 0; i < maximo; i++) { // conferência lexical
            if(toLowerCase(a->lexical[i]) < toLowerCase(b->lexical[i]))
                return 1;
            else if(toLowerCase(a->lexical[i]) > toLowerCase(b->lexical[i]))
                return 0;
        }
        return 0;
    } else
        return a->num < b->num; // conferencia de ordenção numérica
}

void objSelectSort(OBJ** array, int qnt, int op) // select sort com o ponteiro de objetos
{
    for (int i = 0; i < qnt; ++i) { // loop entre os objetos
        int index = i; // index do objeto atual
        for (int j = i; j < qnt; ++j) { // loop entre os próximos objetos
            if(conferencia(array[j], array[index], op)) // caso confira troca
            {
                index = j; // indexa troca
            }
        }
        if (i != index) // se houver troca a ser realizada
        {
            // troca valores
            int tempNum = array[i]->num; char* tempChar = array[i]->lexical;
            array[i]->num = array[index]->num; array[i]->lexical = array[index]->lexical;
            array[index]->num = tempNum; array[index]->lexical = tempChar;
        }
    }
}

int main(void)
{
    int cont = 0; // contador de objetos
    OBJ **objetos = NULL; // lista de objetos

    int op; // opção lida
    op = atoi(leFrase(stdin)); // lê a opção desejada

    do { // loop da leitura de objetos
        char* leitura = leFrase(stdin); // frase lida

        if(strlen(leitura) <= 0) { // se a frase não seja vazia (final de entrada) sai do loop
            op -= 2;
            free(leitura);
            break;
        }

        objetos = realloc(objetos, ++cont * sizeof(OBJ*)); // atualiza tamanho da lista de objetos
        objetos[cont-1] = retornaObj(leitura); // aloca o novo bojeto lido
        free(leitura); // libera memória da frase lida
    } while (op > 0);

    objSelectSort(objetos, cont, op + 2); // ordena a lista de objetos

    for (int i = 0; i < cont; ++i) {
        printf("%d\t%s\n", objetos[i]->num, objetos[i]->lexical); // exibe cada objeto ordenado
    }

    // libera lista de objetos
    for (int i = 0; i < cont; ++i) {
        free(objetos[i]);
    }
    free(objetos);

    return 0;
}