#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int m; // numero de tipos
    float **matriz, // matriz com tipos e multiplicadores
          **ataques = NULL; // possiveis ataques

    scanf("%d", &m); // le o numero de tipos

    // inicializa a matriz de tipos e multiplicadores
    matriz = calloc(m, sizeof(float*));
    for (int i = 0; i < m; i++)
    {
        matriz[i] = calloc(m, sizeof(float));
        for (int j = 0; j < m; j++)
        {
            scanf("%f", &matriz[i][j]);
        }
    }

    int n = 0, te, index; // numero de ataques, tipo do inimigo e indice do melhor ataque
    float f = 0, t, r = -1; // forca do ataque lido, seu tipo e forca resultante
    while (f != -1) // enquanto nao fim de ataques
    {
        scanf("%f", &f); // le a forca do ataque
        if (f == -1) // checa por fim da lista
            break;
        scanf("%f", &t); // tipo do ataque

        ataques = realloc(ataques, ++n * sizeof(float*)); // atualiza tamanho da lista de ataques
        ataques[n-1] = calloc(2, sizeof(float)); // aloca memoria para o novo ataque
        //registra forca e tipo do ataque lido
        ataques[n-1][0] = f;
        ataques[n-1][1] = t;
    }

    scanf("%d", &te); // le tipo do inimigo
    for(int i = 0; i < n; i++)
    {
        // confere todas as combinacoes de forca e tipo dos ataques lidos procurando o maior, atualizando a forca e seu indice
        if(ataques[i][0] * matriz[(int) ataques[i][1]][te] > r)
        {
            r = ataques[i][0] * matriz[(int) ataques[i][1]][te];
            index = i;
        }
    }

    printf("O melhor ataque possui indice %d e dano %.2f\n", index, r); // exibe o ataque resultante mais forte e seu indice

    //libera memoria das matrizes
    for (int i = 0; i < m; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    for (int i = 0; i < n; i++)
    {
        free(ataques[i]);
    }
    free(ataques);

    return 0;
}