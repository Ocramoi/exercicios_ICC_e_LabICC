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
    char *copia = malloc(strlen(original) + 1); strcpy(copia, original); // cria cópia da string original
    char *str = copia; // variável com o ponteiro da string para tratamento

    while (*str) {            // loop entre os bytes do ponteiro
        *str = tolower(*str); // converte cada caracter para minúscula
        str++;                // avança para o próximo byte
    }

    return copia; // retorna a string convertida para facilitar as operações
}

void ordenaNomes(char ***nomes, int qnt) // função de oridenação da lista de nomes (selection sort)
{
    char* temp = NULL; // variável temporária para a troca dos nomes

    for (int i = 0; i < qnt; i++) { // selection sort entre os nomes
        int index = i;

        for (int j = i; j < qnt; j++) {
            if(strcmp(minusculas((*nomes)[j]), minusculas((*nomes)[index])) < 0) index = j;
        }

        if (index != i) { // swap entre as palavras se necessário
            temp = realloc(temp, strlen((*nomes)[i]) + 1); strcpy(temp, (*nomes)[i]);
            (*nomes)[i] = realloc((*nomes)[i], strlen((*nomes)[index]) + 1); strcpy((*nomes)[i], (*nomes)[index]);
            (*nomes)[index] = realloc((*nomes)[index], strlen(temp) + 1); strcpy((*nomes)[index], temp);
        }
    }

    free(temp); // libera a variável auxiliar
}

int main(void)
{
    char *temp,          // variável temporária para a leitura dos nomes digitados
         **nomes = NULL; // vetor da lista de nomes
    int qnt = 0,         // quantidade de nomes na lista
        tempTam;         // variável auxiliar de tamanho de string lida

    do { // loop entre strings significativas
        temp = leFrase(stdin); tempTam = strlen(temp);                                // lê a string e seu tamanho
        if(tempTam == 0) break;                                                       // quebra loop caso string lida tenha tamanho 0
        nomes = realloc(nomes, ++qnt * sizeof(char *));                       // atualiza tamanho da lista
        nomes[qnt - 1] = malloc(tempTam + 1); strcpy(nomes[qnt - 1], temp); // adiciona elemento à lista
    } while (tempTam > 0);

    ordenaNomes(&nomes, qnt); // ordena lista de nomes

    for (int i = 0; i < qnt; i++) { // exibe nomes e libera memória do vetor
        printf("%s\n", nomes[i]);
        free(nomes[i]);
    } free(nomes);

    free(temp); // libera variável temporária de leitura

    return 0;
}