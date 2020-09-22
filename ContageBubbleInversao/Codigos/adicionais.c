#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 64

/**
 * Função para a geração de vetores de tamanho arbitrário
 */
int *gera(int tamanho)
{
    int *retorno = malloc(tamanho * sizeof(int)); // aloca memória para o vetor
    for (int i = 0; i < tamanho; ++i) {           // gera um número pseudo randômico para cada elemento do vetor
        retorno[i] = rand();
    }
    return retorno;
}

int main(void) {
    srand(time(NULL)); // estabelece semente pseurandômica

    for (int i = 1; i <= 10; ++i) { // gera um vetores de tamanho 1000-10000 em incrementos de 1000
        char nomeArq[BUFFER_SIZE]; sprintf(nomeArq, "./Data/numberlist%d.dat", i*1000);
        FILE *arq = fopen(nomeArq, "w+");
        int *vetor = gera(i*1000);

        fwrite(vetor, sizeof(int), i*1000, arq);

        free(vetor); fclose(arq); // fecha o arquivo e livera a memória
    }

    return 0;
}