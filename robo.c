#include <stdio.h>

int main(void)
{
    /// a posição é salva em um char (8 bits) sendo as 4 posições então equivalente a shifts de 2 bits da posição
    unsigned char l, pos = 2; // char de leitura de caracter e de posição
    do {
        l = getc(stdin); // leitura do char
        if(l == 'D') pos = (pos >> 2) | (pos << (8 - 2)); // shift circular à direita se o char lido é 'D'
        else if(l == 'E') pos = (pos << 2) | (pos >> (8 - 2)); // shift circular à esquerda se o char lido é 'E'
    } while (l != '\n'); // quebra de loop caso char seja final de linha
    switch (pos) { // switch de posições, sendo feita a comparação de bit e exibindo a posição final
        case 2:
            printf("Norte\n");
            break;
        case 8:
            printf("Oeste\n");
            break;
        case 32:
            printf("Sul\n");
            break;
        case 128:
            printf("Leste\n");
            break;
    }
    return 0;
}