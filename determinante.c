#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c, l; // variáveis dos números de colunas e linhas
    scanf("%d", &c); // lê o número de colunas
    scanf("%d", &l); // lê o número de linhas
    if((c < 0 || c > 3) || (l < 0 || l > 3)) // se a entrada é inválida
    {
        printf("Entradas invalidas!"); // exibe mensagem
        return 0; // finaliza a execução
    }
    else if(c != l) // se a entrada é matriz sem determinante
    {
        printf("A matriz de entrada nao possui determinante!"); // exibe mensagem
        return 0; // finaliza a execução
    }
    int** matriz = (int**) calloc(l, sizeof(int*)); // inicializa as linhas da matriz na heap
    for(int k = 0; k < l; k++)
    {
        matriz[k] = (int*) calloc(c, sizeof(int)); // inicializa as colunas de cada linha na matriz na heap
    }

    for(int k = 0; k < l; k++)
    {
        for(int i = 0; i < l; i++)
        {
            scanf("%d", &matriz[k][i]); // lê os valores da matriz
        }
    }

    int det; // variável para o valor da determinante
    if (c == 1) det = matriz[0][0]; // se a matriz for de ordem 1, considera seu determinante como o único valor
    else
    {
        // se a matriz for de ordem 2 ou 3, faz o cáculo de seu determinante pelas diagonais
        if(c == 2)
            det = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
        else
            det = ( (matriz[0][0] * matriz[1][1] * matriz[2][2]) +
                    (matriz[0][1] * matriz[1][2] * matriz[2][0]) +
                    (matriz[0][2] * matriz[1][0] * matriz[2][1])) -
                  ( (matriz[0][2] * matriz[1][1] * matriz[2][0]) +
                    (matriz[0][0] * matriz[1][2] * matriz[2][1]) +
                    (matriz[0][1] * matriz[1][0] * matriz[2][2]));
    }
    printf("O determinante da matriz de entrada equivale a %d e tem ordem %d", det, c); // exibe a mensagem final
    return 0;
}