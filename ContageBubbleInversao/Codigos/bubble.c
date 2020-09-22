#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFF_SIZE 64
#define PASSAGENS 1000.

/**
 * Implementação bubble sort
 */
void bubbleSort(int num, int *vec)
{
    char flag = '!';
    while (flag == '!') { // enquanto flag inicial
        flag = '.';
        for (int i = 0; i < (num - 1); ++i) { // para todos os elementos faça troca com o posterior se necessário
            if (vec[i] > vec[i + 1]) {
                flag = '!'; // confere se alteração foi feita
                vec[i] = vec[i] + vec[i + 1];
                vec[i + 1] = vec[i] - vec[i + 1];
                vec[i] = vec[i] - vec[i + 1];
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: ./bubble [nome do arquivo de entrada] >> [arquivo de saída]\n");
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

    int *temp = malloc(num * sizeof(int)),
        *vec =  malloc(num * sizeof(int)); fread(vec, sizeof(int), num, entrada); // cria os vetores necessários
    long double tempo = 0;
    clock_t init,
            fim;

    fclose(entrada);
    for (int i = 0; i < PASSAGENS; ++i) { // realiza o número de passagens estabelecido
        memcpy(temp, vec, num * sizeof(int)); // cria uma cópia do vetor

        // lê o tempo entre a execução
        init = clock();
        bubbleSort(num, temp);
        fim = clock();

        tempo += (long double)(fim - init)/CLOCKS_PER_SEC; // calcula o tempo elapsado em segundos
    }

    printf("%d %Lf\n", num, tempo/PASSAGENS); // exibe o número de elementos do vetor e o tempo elapsado
    
    free(vec); free(temp); // libera memória alocada
    return 0;
}