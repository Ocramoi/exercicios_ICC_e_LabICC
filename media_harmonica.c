#include <stdio.h>

int main(int argc, char* argv[])
{
    int n; // número de valores a srem lidos
    scanf("%d", &n); // lê o número de valores a srem lidos

    float divisor = 0; // inicializa o divisor em 0

    for(int k = 0; k < n; k++)
    {
        float temp; // valor digitado
        scanf("%f", &temp); // lê o valor digitado
        divisor += 1/(temp + 1); // atualiza o divisor com o valor digitado
    }

    float media = ((float)n/divisor) - 1; // calcula a média de acordo com a fórmula

    printf("%.2f", media); // exibe a média com 2 casas decimais

    return 0;
}