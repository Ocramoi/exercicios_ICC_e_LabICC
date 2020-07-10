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

    while (nomes == NULL || nomes[nNomes - 1][strlen(nomes[nNomes - 1]) - 1] != '$') // loop para a leitura dos nomes
    {
        nomes = realloc(nomes, ++nNomes * sizeof(char*)); // atualiza tamanho do vetor de nomes
        nomes[nNomes - 1] = leFrase(stdin); // le nome digitado
    }

    nomes[nNomes - 1][strlen(nomes[nNomes - 1]) - 1] = '\0'; // limpa final de lista do ultimo elemento

    for(int i = 0; i < nNomes; i += 2) // loop entre elementos pares
    {
        if(i + 1 >= nNomes) // confere se ha um proximo elemento
            break;

        int ult = 0; // variavel para o indice do ultimo espaco
        for(int j = strlen(nomes[i]) - 1; j >= 0; j--) // percorre a string de tras para frente procurando por espacos em branco
        {
            if (nomes[i][j] == ' ') // salva o indice do primeiro espaco em branco achado, ultimo da string
            {
                ult = j;
                break;
            }
        }

        nomes[i+1] = realloc(nomes[i+1], (strlen(nomes[i+1]) + (strlen(nomes[i]) - ult)) + 1); // atualiza o tamanho do proximo nome
        strcpy(&nomes[i+1][strlen(nomes[i+1])], &nomes[i][ult]); // adiciona o trecho apos o ultimo espaco ao proximo elemento
    }

    // limpa variaveis dinamicas
    for (int i = 0; i < nNomes; i++)
    {
        printf("%s\n", nomes[i]);
        free(nomes[i]);
    }
    free(nomes);

    return 0;
}