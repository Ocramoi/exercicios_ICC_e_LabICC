#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 256 // buffer do realloc de string

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

int main(int argc, char** argv)
{
    int nNomes = 0; // variavel para a quantidade de nomes lidos
    char **nomes = NULL; // matriz para armazenamento dos nomes lidos

    while (nomes == NULL || nomes[nNomes - 1][strlen(nomes[nNomes - 1]) - 1] != '$'){ // loop para a leitura dos nomes
        nomes = realloc(nomes, ++nNomes * sizeof(char*)); // atualiza tamanho do vetor de nomes
        nomes[nNomes - 1] = leFrase(stdin); // le nome digitado
    }

    nomes[nNomes - 1][strlen(nomes[nNomes - 1]) - 1] = '\0'; // limpa final de lista do ultimo elemento

    char *surP = NULL, *surS = NULL; // inicializa variaveis auxiliares para os dois sobrenomes a serem trocados
    for(int i = 0, j = nNomes - 1; i < nNomes/2; i++, j--) { // percorre pelos indices de pares de nomes ao fim e comeco da lista
        int ultP,
            ultS; // variaveis para indicar o inicio do ultimo sobrenome

        // encontra o inicio do ultimo sobrenome de cada nome (primeiro espaço em branco do fim ao começo)
        for(int k = strlen(nomes[i]) - 1; k >= 0; k--) {
            if(nomes[i][k] == ' ') {
                ultP = k;
                break;
            }
        }
        for(int k = strlen(nomes[j]) - 1; k >= 0; k--) {
            if(nomes[j][k] == ' ') {
                ultS = k;
                break;
            }
        }

        // aloca espaço para salvar os sobrenomes a serem invertidos
        surP = realloc(surP, (strlen(nomes[i]) - ultP + 1) * sizeof(char)); strcpy(surP, nomes[i] + ultP);
        surS = realloc(surS, (strlen(nomes[j]) - ultS + 1) * sizeof(char)); strcpy(surS, nomes[j] + ultS);

        // salva efetivamente os dois sobrenomes
        nomes[i] = realloc(nomes[i], (strlen(nomes[i]) - (strlen(surP) - strlen(surS)) + 1) * sizeof(char));
        nomes[j] = realloc(nomes[j], (strlen(nomes[j]) - (strlen(surS) - strlen(surP)) + 1) * sizeof(char));

        // copia para os elementos da lista os sobrenome já trocados
        strcpy(nomes[i] + ultP, surS);
        strcpy(nomes[j] + ultS, surP);
    }
    free(surP); free(surS); // libera as variaveis temporarias de sobrenomes

    // limpa variaveis dinamicas
    for (int i = 0; i < nNomes; i++)
    {
        printf("%s\n", nomes[i]);
        free(nomes[i]);
    }
    free(nomes);

    return 0;
}