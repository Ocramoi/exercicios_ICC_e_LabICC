#include <stdio.h>

int readInt() // função de leitura de inteiro
{
    int r; // inicializa inteiro
    scanf("%d", &r); // lê inteiro
    return r; // retorna o valor lido
}

double readDouble() // função de leitura de double
{
    double r; // inicializa double
    scanf("%lf", &r); // lê double
    return r; // retorna o valor lido
}

void printDouble(double val) // função de exibição de double
{
    printf("%.2lf\n", val); // exibe a média com 2 casas decimais
}

int main(int argc, char* argv[])
{
    int n = readInt(); // lê o número de valores a srem lidos

    double divisor = 0; // inicializa o divisor em 0

    for(int k = 0; k < n; k++)
    {
        double temp = readDouble(); // lê o valor digitado
        divisor += 1/(temp + 1); // atualiza o divisor com o valor digitado
    }

    double media = ((double)n/divisor) - 1; // calcula a média de acordo com a fórmula

    printDouble(media); // exibe a média com 2 casas decimais

    return 0;
}