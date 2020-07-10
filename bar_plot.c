#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num, qnt; // variáveis do número de barras e da quantidade de dados
    scanf("%d", &num); // lê a quantidade de barras
    scanf("%d", &qnt); // lê a quantidade de dados
    int* vals = (int*) calloc(num, sizeof(int)); // reserve na heap um vetor com a quantidade de valores necessários e os inicializa em 0
    int temp; //variável temporária do valor a ser lido
    for(int k = 0; k < qnt; k++) // loop pela quantidade de valores a serem digitados
    {
        scanf("%d", &temp); // lê o valor digitado
        vals[temp] += 1; // soma uma ocorrência desse valor
    }
    for(int k = 0; k < num; k++) // loop pela quantidade de barras
    {
        printf("%d - ", k); // exibe a "legenda" da barra
        for(int j = 0; j < vals[k]; j++) // loop pelo valor dessa legenda
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}