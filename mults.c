#include <stdio.h>

int main(void)
{
    int n, i, j, cont = 0, val = 0; // inteiros da quantidade de valores a serem exibidos, primeiro valor, segundo valor e valor de teste
    scanf("%d", &n); // lê a quantidade de valores a serem exibidos
    scanf("%d", &i); // lê o primeiro valor
    scanf("%d", &j); // lê o segundo valor
    while (cont < n) // loop até a quantidade desejada de valores foi exibida
    {
        if(val % i == 0 || val % j == 0) // se o valor de teste é múltiplo de um dos valores
        {
            printf("%d\n", val); // exibe o valor
            cont++; // atualiza o contador
        }
        val++; // atualiza o valor de teste
    }
    return 0;
}