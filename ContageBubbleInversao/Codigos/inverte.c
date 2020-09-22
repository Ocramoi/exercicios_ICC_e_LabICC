#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE 64
#define PASSAGENS 1000.

/**
 * Função de inversão de vetor
 */
void inverteVetor(int num, int *vec) 
{
    for (int i = 0; i < (num - 1)/2; ++i) { // para cada dupla de elementos, realiza a troca
        vec[i] = vec[i] + vec[(num - 1) - i];
        vec[(num - 1) - i] = vec[i] - vec[(num - 1) - i];
        vec[i] = vec[i] - vec[(num - 1) - i];
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: ./inverte [nome do arquivo de entrada] >> [arquivo de saída]\n");
        return 1;
    } // confere entrada do programa

    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Erro na abertura de arquivo!\n");
        return 1;
    } // abertura segura de arquivo

    fseek(entrada, 0, SEEK_END);
    int num = ftell(entrada)/sizeof(int);
    fseek(entrada, 0, SEEK_SET); // calcula a quantidade de elementos no arquivo

    int *vec = malloc(num * sizeof(int)); fread(vec, sizeof(int), num, entrada);
    long double tempo = 0;
    clock_t init,
            fim;

    for (int i = 0; i < PASSAGENS; ++i) { // realiza o número de passagens estabelecido
        // lê o tempo entre a execução
        init = clock();
        inverteVetor(num, vec);
        fim = clock();

        tempo += (long double)(fim - init)/CLOCKS_PER_SEC; // calcula o tempo elapsado em segundos
    }

    printf("%d %Lf\n", num, tempo/PASSAGENS); // exibe o número de elementos do vetor e o tempo elapsado
    
    fclose(entrada); free(vec); // libera memória alocada
    return 0;
}