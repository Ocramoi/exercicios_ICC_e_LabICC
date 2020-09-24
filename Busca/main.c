#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int tipo;
    int elem;
} BUSCA; // estrutura de busca

int buscaSequencial(int size, int *regs, int key)
{
    for (int i = 0; i < size; ++i) 
        if (regs[i] == key) return i + 1; // percorre o vetor a procura do elemento buscado

    return -1; // caso de erro
}

int buscaBinIter(int ini, int fim, int *regs, int key)
{
    while (ini <= fim) { // enquanto válida a pesquisa
        int mid = ini + (fim - ini)/2;
        if (regs[mid] == key) 
            return mid + 1;       // retorna o elemento médio se correto
        else if (regs[mid] > key) // atualiza os extremos do vetor caso contrário
            fim = mid - 1;
        else
            ini = mid + 1;
    }
    
    return -1; // caso de erro
}

int buscaBinRecur(int ini, int fim, int *regs, int key)
{
    if (fim < ini) return -1; // caso de erro

    int mid = ini + (fim - ini)/2;

    if (regs[mid] == key) 
        return mid + 1;       // retorna elemento médio se correto
    else if (regs[mid] > key) // realiza a pesquisa nos subvetores se necessário
        return buscaBinRecur(ini, mid - 1, regs, key);
    else
        return buscaBinRecur(mid + 1, fim, regs, key);
}

int main(void)
{
    int nRegistros,
        nBuscas;
    scanf("%d %d", &nRegistros, &nBuscas); // infos de pesquisa

    int *regs = malloc(nRegistros * sizeof(int));
    for (int i = 0; i < nRegistros; ++i)
        scanf("%d", &regs[i]); // lê registros para pesquisa

    BUSCA *buscas = malloc(nBuscas * sizeof(BUSCA));
    for (int i = 0; i < nBuscas; ++i)
        scanf("%d %d", &buscas[i].tipo, &buscas[i].elem); // lê as diferentes buscas na estrutura criada

    for (int i = 0; i < nBuscas; ++i) {
        switch(buscas[i].tipo) { // realiza a busca correta para o tipo selecionado
            case 1:
                printf("%d\n", buscaSequencial(nRegistros, regs, buscas[i].elem));
                break;
            case 2:
                printf("%d\n", buscaBinIter(0, nRegistros - 1, regs, buscas[i].elem));
                break;
            case 3: 
                printf("%d\n", buscaBinRecur(0, nRegistros - 1, regs, buscas[i].elem));
            default:
                break;
        }
    }

    return 0;
}