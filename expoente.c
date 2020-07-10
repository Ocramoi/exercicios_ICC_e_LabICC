#include <stdio.h>

int main(void)
{
    double base, val = 1; // valores da base e valor final
    int exp; // valor do expoente
    scanf("%lf", &base); // lê o valor para a base
    scanf("%d", &exp); // lê o valor para o expoente
    for(int k = 0; k < exp; k++) // loop pelo valor do expoente
    {
        val *= base; // multiplica o valor pela base
    }
    printf("%.4f", val); // exibe o valor com 4 casas decimais
    return 0;
}