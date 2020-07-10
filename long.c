#include <stdio.h>

int main(int argc, char* argv[])
{
    unsigned long long n; // variável para o valor a ser lido (long long -> 8 bytes)
    scanf("%lld", &n); // lê o valor digitado

    unsigned char* val = (unsigned char*) &n; // cria um vetor de chars a partir do espaço de memória do valor lido (8 bytes -> 8 chars)
    for(int k = 0; k < sizeof(long long); k++)
    {
        printf("%x\n", val[k]); // exibe cada valor lido como char com máscara hexadecimal
    }

    return 0;
}