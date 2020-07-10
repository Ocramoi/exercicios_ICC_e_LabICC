#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int n,      // número de linhas do mapa
        m,      // número de colunas do mapa
        x,      // linha posição inicial
        y,      // coluna da posição inicial
        **mapa, // vetor bidimensional do mapa
        bX, bY; // posição da base
    double mv;  // atributo de movimento

    scanf("%d %d %d %d %lf", &n, &m, &x, &y, &mv); // lê os valores inseridos
    mapa = malloc(n * sizeof(int *));                // aloca linhas do vetor do mapa

    for (int i = 0; i < n; i++) {                 // loop entre as linhas do mapa
        mapa[i] = malloc(m * sizeof(int *)); // aloca as colunas da linha
        for (int j = 0; j < m; j++) {             // lê os valores de todas as células da linha
            scanf("%d", &mapa[i][j]);
            if (mapa[i][j] == 1) { // se o valor da célula for 1 (base), armazena sua posição
                bX = i;
                bY = j;
            }
        }
    }

    if (sqrt(pow(bX - x, 2) + pow(bY - y, 2)) <= mv) printf("Voce escapou!\n"); // confere a distância euclidiana entre os pontos
    else printf("Game Over!\n");

    for (int i = 0; i < n; i++) { // libera memória do vetor do mapa
        free(mapa[i]);
    } free(mapa);

    return 0;
}