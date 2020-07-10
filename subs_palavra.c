#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void)
{
    char *trechoA = leFrase(stdin), // variável para a frase a ser sunbstituída
         *trechoB = leFrase(stdin), // variável para a frase de substituição
         *frase = leFrase(stdin); // variável para a frase completa

    unsigned long long lenA = strlen(trechoA), lenB = strlen(trechoB); // tamanhos do trecho A e B em caracteres

    for(int k = 0; k <= strlen(frase) - lenA; k++) // loop pelos agrupamentos de caracteres de tamanho de A
    {
        char* temp = (char*) malloc((lenA + 1) * sizeof(char)); // variável temporária para o agrupamento lido
        memcpy(temp, frase+k, lenA); // copia o agrupamento para a variável
        temp[lenA] = '\0'; // inclui o caracter de final de string
        if(strcmp(temp, trechoA) == 0) { // confere se o agrupamento é igual ao trecho a ser substituído
            char *nova = (char*) malloc((strlen(frase) - (lenA - lenB) + 1) * sizeof(char)); // variável para a frase alterada com tamanho atualizado
            for(int i = 0; i < k; i++)
            {
                nova[i] = frase[i]; // copia todos os caracteres anteriores ao agrupamento que permanecerão iguais para a nova string
            }
            for(int i = 0; i < lenB; i++)
            {
                nova[k+i] = trechoB[i]; // no lugar dos caracteres a serem substituídos adiciona as substituições
            }
            for(int i = k; i < strlen(frase) - lenA; i++)
            {
                nova[i+lenB] = frase[i+lenA]; // adiciona o resto dos caracteres que permanecerão iguais
            }
            nova[strlen(frase) - (lenA - lenB)] = '\0'; // adiciona o caracter de final de string
            frase = (char*) realloc(frase, (strlen(nova) + 1) * sizeof(char)); // atualiza o tamanho do ponteiro da frase
            memcpy(frase, nova, strlen(nova) * sizeof(char)); // copia a frase alterada para o ponteiro da frase
            frase[strlen(nova)] = '\0'; // inclui o caracter de final de linha à frase alterada
            free(nova); // libera a memória da frase alterada temporária
        }
        free(temp); // libera a memória da frase de agrupamento
    }

    printf("%s\n", frase); // exibe a frase alterada

    // libera ponteiros dos parâmetros iniciais
    free(trechoA);
    free(trechoB);
    free(frase);

    return 0;
}