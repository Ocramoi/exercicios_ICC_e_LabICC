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

char *maiusculas(char *original) // função de conversão de strings para maiúsculas
{
    char *str = original; // variável com o ponteiro da string para tratamento

    while (*str) {            // loop entre os bytes do ponteiro
        *str = toupper(*str); // converte cada caracter para maiúscula
        str++;                // avança para o próximo byte
    }

    return original; // retorna a string convertida para facilitar as operações
}

int main(void)
{
    char *autor = leFrase(stdin), // nome do autor inserido
         *abnt = calloc(strlen(autor) + 2, sizeof(char)); // string convertida
    int espaco = 0; // localização do último espaço

    for (int i = strlen(autor) - 1; i >= 0; i--) { // procura o último espaço no nome (último sobrenome)
        if (autor[i] == ' ') {
            espaco = i + 1;
            break;
        }
    }

    strncpy(abnt, autor + espaco, strlen(autor) - espaco); maiusculas(abnt); // copia o último nome em maiúsculas
    abnt[strlen(abnt)] = ','; abnt[strlen(abnt)] = ' '; // adiciona a vírgula e espaçoes adicionais

    strncpy(abnt + strlen(abnt), autor, strlen(autor) - (strlen(autor) - espaco)); // copia o resto do nome

    printf("%s\n", abnt); // escibe o nome convertido

    free(autor); free(abnt); // libera os ponteiros usados

    return 0;
}