#include <stdio.h>
#include <stdlib.h>
#define NUM_VALS 31 // define número de valores a serem lidos

int main(void)
{
    int* vals = (int*) malloc(NUM_VALS * sizeof(int)); // inicializa o vetor de inteiros na heap
    for(int k = 0; k < NUM_VALS; k++) // para o número de valores a serem lidos
    {
        scanf("%d", &vals[k]); // lê o valor para sua posição
    }
    for(int k = 0; k < NUM_VALS - 1; k++) // para o número de valores a serem comparados com o último
    {
        if(vals[k] % vals[NUM_VALS-1] == 0) // se divisível pelo úlitmo valor
            printf("%d\n", vals[k]); // exibe o valor
    }
    return 0;
}