#include <stdio.h>
#include <stdlib.h>

int** leMatriz() // funcao de leitura da matriz
{
    // aloca matriz a ser lida
    int** retorno = calloc(6, 3 * sizeof(int));

    for(int i = 0; i < 6; i++)
    {
        // aloca e le linhas da matriz
        retorno[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &retorno[i][j]);
        }
    }

    return retorno; // retorna a matriz lida
}

int** misturaCor(int** matriz, int mistura1, int mistura2, int r) // funcao de mistura das cores
{
    int** retorno = calloc(6, 3 * sizeof(int)); // inicializa a matriz das cores misturadas

    for(int i = 0; i < 6; i++)
    {
        // inicializa e copia linhas da matriz nova
        retorno[i] = malloc(3 * sizeof(int));
        retorno[i][0] = matriz[i][0];
        retorno[i][1] = matriz[i][1];
        retorno[i][2] = matriz[i][2];
    }

    // mistura os três componentes da cor
    retorno[r][0] = ((retorno[mistura1][0] + retorno[mistura2][0])/2 + retorno[r][0] < 256) ? (retorno[mistura1][0] + retorno[mistura2][0])/2 + retorno[r][0] : 255;
    retorno[r][1] = ((retorno[mistura1][1] + retorno[mistura2][1])/2 + retorno[r][1] < 256) ? (retorno[mistura1][1] + retorno[mistura2][1])/2 + retorno[r][1] : 255;
    retorno[r][2] = ((retorno[mistura1][2] + retorno[mistura2][2])/2 + retorno[r][2] < 256) ? (retorno[mistura1][2] + retorno[mistura2][2])/2 + retorno[r][2] : 255;

    return retorno; // retorna a matriz da mistura
}

void exibeMatrizes(int** original, int** misturada) // funcao de exibicao e desalocacao das matrizes
{
    // exibe e desaloca a memoria de ambas as matrizes
    printf("Start:\n");
    for(int i = 0; i < 6; i++)
    {
        printf("Color(%d): [\t%d\t%d\t%d\t]\n", i, original[i][0], original[i][1], original[i][2]);
        free(original[i]);
    }
    free(original);

    printf("\nResult:\n");
    for(int i = 0; i < 6; i++)
    {
        printf("Color(%d): [\t%d\t%d\t%d\t]\n", i, misturada[i][0], misturada[i][1], misturada[i][2]);
        free(misturada[i]);
    }
    free(misturada);
}

int main(int argc, char** argv)
{
    int cor1, cor2, res; // indices das cores a serem misturadas e da mistura
    scanf("%d %d %d", &cor1, &cor2, &res); // le indices das cores a serem misturadas e da mistura

    int **coresRGB = leMatriz(), // cria e le matriz das cores
        **coresMistura = misturaCor(coresRGB, cor1, cor2, res); // mistura as cores desejadas

    exibeMatrizes(coresRGB, coresMistura); // exibe e libera as matrizes

    return 0;
}