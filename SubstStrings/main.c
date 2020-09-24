#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 128 // buffer do realloc de string

char *readLine (FILE* entrada) { // função que lê string com tratamento
    char *retorno = NULL; // inicializa o ponteiro da frase lida
    int cont = 0; // inicializa a varável que auxiliará o tratamento de tamanho

    do {
        if (cont % STR_BUFFER == 0) { // conferência do tamanho como próximo múltiplo do buffer
            retorno = (char* ) realloc(retorno, ((cont/STR_BUFFER + 1) * STR_BUFFER) * sizeof(char)); // aumenta o tamanho da string em função do buffer caso tenha ultrapassado um novo múltiplo, diminuindo o gasto computacional com realocação
        }
        retorno[cont] = fgetc(entrada); // lê novo caracter
        cont++; // atualiza o tamanho da string
    } while (retorno[cont-1] != '\n' && retorno[cont-1] != EOF); // repete até o final da leitura de string

    if (cont >= 2 && retorno[cont - 2] == '\r') { // confere pelo caracter de formatação '\r'
        retorno[cont - 2] = '\0'; // substitui o caracter por fim de string
        retorno = (char* ) realloc(retorno, (cont-1) * sizeof(char)); // diminui o tamanho da string em 1 caracter
    }
     else {
        retorno[cont-1] = '\0'; // formata a string com o caracter de final de string
        retorno = (char* ) realloc(retorno, cont * sizeof(char)); // realoca o ponteiro da string para seu tamanho desconsiderando o buffer
    }

    return retorno;
}

char *corrigeStr(char *original, char *erro, char *correcao) // corrige a string original em função dos parâmetros
{
    char *temp = NULL,                                                          // string auxiliar para modificação
         *alterada = malloc(strlen(original) + 1); strcpy(alterada, original);  // string alterada final

    for (int i = 0; i < strlen(alterada); ++i) {
        if (alterada[i] != erro[0]) continue; // executa apenas se primeira letra coincidente

        if (!memcmp(alterada + i, erro, strlen(erro))) { // se o trecho bate
            temp = realloc(temp, strlen(alterada) - strlen(erro) + strlen(correcao) + 1);
            memcpy(temp, alterada, i);
            memcpy(temp + i, correcao, strlen(correcao));
            strcpy(temp + i + strlen(correcao), alterada + i + strlen(erro)); // copia a string anterior modificando a região errada
            alterada = realloc(alterada, strlen(temp) + 1);
            strcpy(alterada, temp); // atualiza a string alterada
        }
    }
    
    free(temp); // libera memória auxiliar
    return alterada;
}

int main(void)
{
    char *original = NULL,
         *erro = NULL,
         *correcao = NULL; // entradas a serem lidas
    do { // lê até o final da entrada
        free(original); free(erro); free(correcao); // libera leitura anterior
        original = readLine(stdin);
        if (original[0] == '\0') break;
        erro = readLine(stdin);
        correcao = readLine(stdin); // lê os valores checando pelo fim do arquivo
        
        char *alterada = corrigeStr(original, erro, correcao);
        printf("%s\n", alterada);
        free(alterada); // gera e exibe a string alterada
    } while(original[0] != '\0');

    free(original); // libera memória
    return 0;
}