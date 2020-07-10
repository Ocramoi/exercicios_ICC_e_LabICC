#include <stdio.h>
#include <stdlib.h>

void ordArray(char **chars, int num) // função de ordenação da lista de caracteres
{
    // selection sort de caracteres
    int index;
    for (int i = 0; i < num; i++) {
        index = i;

        for (int j = i; j < num; j++)
            if((*chars)[j] < (*chars)[index]) index = j;

        if (index != i) {
            char temp = (*chars)[index];
            (*chars)[index] = (*chars)[i];
            (*chars)[i] = temp;
        }
    }
}

int main(void)
{
    char *caracteres = NULL, // inicializa lista de caracteres a ser lida
          temp;              // variável auxiliar de leitura de caracteres
    int nCaracteres = 0;     // inicializa variável auxiliar com o número de caracteres lidos

    do {
        scanf("%c", &temp); // lê o caracter inserido
        if(temp == '\n' || temp == '\r' || temp == '\t') continue; // trata por caracteres não representativos
        caracteres = realloc(caracteres, ++nCaracteres * sizeof(char)); // atualiza tamanho da lista
        caracteres[nCaracteres - 1] = temp; // adiciona elemento lido à lista
    } while (temp != 'x'); // lê até encontrar 'x'

    ordArray(&caracteres, nCaracteres); // ordena lista

    unsigned int *vetor = (unsigned int *) caracteres; // cria representação do segmento de memória da lista como uma de inteiros
    for (int i = 0; i < nCaracteres/4; ++i) { // percorre a nova lista (com um quarto do tamanho, sendo o tamanho de cada elemento quatro vezes maior)
        printf("%u\n", vetor[i]); // exibe o valor
    }
    free(caracteres); // libera vetor da lista

    return 0;
}