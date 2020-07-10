#include <stdio.h>

int proximoPrimo(int atual) // função que retorna o próximo primo a partir do enviado por argumento
{
    int retorno = -1; // inicia o retorno como -1
    atual++; // atualiza o valor enviado para próximo inteiro
    while (retorno < 0) // loop até retorno válido
    {
        int cont = 0; // inicia contador de divisíveis
        for(int k = 1; k <= atual; k++) // loop de 1 até o argumento atualizado
        {
            if (atual % k == 0) // se divisível pelo int do loop
            {
                cont++; // conta um divisível
            }
        }
        if(cont == 2) // se tiveream apenas 2 divisíveis (1 e ele mesmo)
        {
            retorno = atual; // próximo primo é o argumento atualizado
            break;
        }
        atual++; // atualiza o argumento para o próximo inteiro
    }
    return retorno; // retorno o próximo primo
}

int main(int argc, char* argv[])
{
    int n, temp, primo = 1; // inicializa inteiros de número a ser decomposto, sua cópia a ser trabalhada e o primeiro primo, respectivamente
    scanf("%d", &n); // lê o valor desejado

    temp = n; // cria uma cópia do valor lido em temp
    while (temp > 1) // loop até uma divisão de quociente 1 do valor lido e processado
    {
        primo = proximoPrimo(primo); // atualiza o próximo primo
        int cont = 0; // inicializa contador
        while (temp % primo == 0) // se o valor lido e/ou processado é divisível pelo primo
        {
            cont++; // soma um ao contador de divisões
            temp /= primo; // divide o valor pelo primo
        }
        if (cont > 0) // se foi possível a divisão
        {
            printf("%d %d\n", primo, cont); // exibe o número de divisões e primo pelo qual foi dividido
        }
    }

    return 0;
}