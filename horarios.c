#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definições de unidades de tempo em segundo
#define DIAS    (24 * 60 * 60)
#define HORAS   (60 * 60)
#define MINUTOS (60)

void calcula(unsigned long long qnt, int planeta,
             unsigned long long *dias, unsigned long long *horas, unsigned long long *minutos, unsigned long long *segundos) // função que calcula os equivalentes em cada planeta
{
    unsigned long long planetas[4] = { 1 * DIAS,
                                       243 * DIAS,
                                       58 * DIAS + 16 * HORAS,
                                       9 * HORAS + 56 * MINUTOS }; // equivalente do dia em segundos de todos os planetas

    // calcula os valores de dias, horas, minutos e segundos
    *dias     = qnt/planetas[planeta];    qnt %= planetas[planeta];
    *horas    = qnt/HORAS;                qnt %= HORAS;
    *minutos  = qnt/MINUTOS;              qnt %= MINUTOS;
    *segundos = qnt;
}

int main(void)
{
    unsigned long long qntSeg,
                       dias,
                       horas,
                       minutos,
                       segundos; // variáveis para o valor em segundos lidos e os futuros equivalente
    char *planetaStr = calloc(9, sizeof(char)); // vetor da string lida
    int planetaOp = -1; // variável da opção de planeta
    scanf("%llu %s", &qntSeg, planetaStr); // leitura dos valores inseridos

    // confere o planeta desejado
    if      (!strcmp("Terra",    planetaStr)) planetaOp = 0;
    else if (!strcmp("Venus",    planetaStr)) planetaOp = 1;
    else if (!strcmp("Mercurio", planetaStr)) planetaOp = 2;
    else if (!strcmp("Jupiter",  planetaStr)) planetaOp = 3;

    calcula(qntSeg, planetaOp, &dias, &horas, &minutos, &segundos); // calcula os equivalentes no planeta inserido

    printf("%llu segundos no planeta %s equivalem a:\n%llu dias, %llu horas, %llu minutos e %llu segundos\n",
           qntSeg, planetaStr, dias, horas, minutos, segundos); // exibe os valores

    free(planetaStr); // libera a memória do vetor
    return 0;
}