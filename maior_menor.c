#include <stdio.h>

int main(void)
{
    int n, min, max, temp; // variáveis do número de valores, valor mínimo e máximo e variável para a leitura dos valores, respectivamente
    scanf("%d", &n); // lê o número de valores a ser digitados
    for (int k = 0; k < n; k++) // loop pelo número de valores desejados
    {
        scanf("%d", &temp); // lê o valor digitado
        if (k == 0) // caso seja o primeiro valor digitado
        {
            // inicializa ambos valores como o digitado
            min = temp;
            max = temp;
        }
        else if(temp < min) min = temp; // se valor digitado menor que o mínimo, atualiza o mínimo
        else if(temp > max) max = temp; // se valor digitado maior que o máximo, atualiza o máximo
    }
    printf("max: %d\nmin: %d\n", max, min); // exibe os valores
    return 0;
}