#include <stdio.h>

int main(int argc, char** argv)
{
	double temp, max = 0; // valores de leitura e máximo, respectivamente
	int mes; // valor do mês resultante

	for(int k = 0; k < 12; k++) // loop entre todos os meses
	{
		scanf("%lf", &temp); // lê o valor do mês
		if(temp > max) // se valor lido maior que o máximo
		{
			max = temp; // atualiza máximo
			mes = k+1; // atualiza mês
		}
	}

	printf("%d %.2lf\n", mes, max); // exibe mês max e seu valor

	return 0;
}
