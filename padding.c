#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int c, r, p, // variaveis para o valor das quantidades de colunas, linhas e valor de padding
        **imagemOriginal, // matriz para a imagem original
        **imagemProcessada; // matriz para a imagem processada

    scanf("%d %d", &c, &r); // le numero de colunas e linhas

    // aloca e le a imagem original com o tamanho digitado
    imagemOriginal = malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++)
    {
        imagemOriginal[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++)
            scanf("%d", &imagemOriginal[i][j]);
    }

    scanf("%d", &p); // le o valor de padding

    // inicializa a imagem processada com o tamanho adicionado
    imagemProcessada = malloc((r + 2*p) * sizeof(int*));
    for (int i = 0; i < r + 2*p; i++)
        imagemProcessada[i] = calloc(c + 2*p, sizeof(int));

    // adiciona ao espaco central (desconsiderando as bordas [padding]) a imagem original
    for (int i = p; i < r+p; i++) {
        for (int j = p; j < c+p; j++)
            imagemProcessada[i][j] = imagemOriginal[i-p][j-p];
    }

    // exibe a imagem processada
    for(int i = 0; i < r+2*p; i++) {
        for (int j = 0; j < c+2*p; j++)
            printf("%d ", imagemProcessada[i][j]);

        printf("\n");
    }

    printf("\n");

    // exibe a imagem original
    for(int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            printf("%d ", imagemOriginal[i][j]);

        printf("\n");
    }

    return 0;
}