#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_BUFFER 64 // buffer do realloc de string

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

char *minusculas(char *original) // função de conversão de strings para minúsculas
{
    char *str = original; // variável com o ponteiro da string para tratamento

    while (*str) {            // loop entre os bytes do ponteiro
        *str = tolower(*str); // converte cada caracter para minúscula
        str++;                // avança para o próximo byte
    }

    return original; // retorna a string convertida para facilitar as operações
}

char **particionaFrase(char *frase, int *qntPalavras) // função que particiona a frase entre palavras
{
    char** retorno = NULL; // inicializa vetor de retorno das palavras
    int qnt = 0;           // variável auxiliar com a quantidade de palavras

    int init = 0; // variável de início de posição da palavra atual na frase
    for (int i = 0; i <= strlen(frase); i++) {                                     // loop entre caracteres da frase (final de string incluso para leitura da última palavra)
        if(frase[i] == ' ' || i == strlen(frase)) {                                // procura por espaços e o fim da string, que marcam fim de palavras
            retorno = realloc(retorno, ++qnt * sizeof(char *));            // adiciona o espaço da palavra a ser adicionada no vetor
            retorno[qnt - 1] = malloc((i - init + 1) * sizeof(char));         // aloca o tamanho correto de caracteres ao elemento novo do vetor
            strncpy(retorno[qnt - 1], frase + init, i - init); // copia a quantidade de caracteres entre os espaços para o elemento do vetor
            retorno[qnt - 1][i - init] = '\0';                                     // adiciona o final de string
            init = i + 1;                                                          // atualiza início da nova palavra
        }
    }

    *qntPalavras = qnt; // indica a quantidade de palavras
    return retorno;     // retorna o vetor
}

void ordenaPalavras(char ***palavras, int qnt)
{
    char* temp = NULL; // variável temporária para a troca das strings

    for (int i = 0; i < qnt; i++) { // selection sort entre as palavras
        int index = i;

        for (int j = i; j < qnt; j++) {
            if(strcmp(minusculas((*palavras)[j]), minusculas((*palavras)[index])) < 0) index = j;
        }

        if (index != i) { // swap entre as palavras se necessário
            temp = realloc(temp, strlen((*palavras)[i]) + 1); strcpy(temp, (*palavras)[i]);
            (*palavras)[i] = realloc((*palavras)[i], strlen((*palavras)[index]) + 1); strcpy((*palavras)[i], (*palavras)[index]);
            (*palavras)[index] = realloc((*palavras)[index], strlen(temp) + 1); strcpy((*palavras)[index], temp);
        }
    }

    free(temp); // libera a variável auxiliar
}

void exibePalavras(char ***palavras, int qnt)
{
    for (int i = 0; i < qnt; i++) { // loop entre as palavras, exibindo-as e liberando a memória
        printf("%s\n", (*palavras)[i]);
        free((*palavras)[i]);
    }
    free(*palavras); // libera a memória do ponteiro de vetor
}

int main(void)
{
    char *fraseLida, // ponteiro da frase lida
         **palavras; // vetor das palavras
    int qntPalavras, // quantidade de palavras no vetor
        op;          // opção de execução

    fraseLida = leFrase(stdin);                          // lê a frase inserida
    op = leFrase(stdin)[0] - 48;                         // lê a opção de execução
    palavras = particionaFrase(fraseLida, &qntPalavras); // particiona a frase e salva o vetor
    if(op == 2) ordenaPalavras(&palavras, qntPalavras);  // caso seja necessário, ordena o vetor
    exibePalavras(&palavras, qntPalavras);               // exibe as palavras do vetor e libera sua memória

    return 0;
}