#include <stdio.h>
#include <stdlib.h>

void leElementos(int **elementos, int qnt) // função de leitura dos elementos
{
    for(int i = 0; i < qnt; i++) { // lê a quantidade de valores digitada
        scanf("%d", &(*elementos)[i]);
    }
}

void ordenaElementos(int **elementos, int qnt) // função de ordenação do array lido
{
    for (int i = 0; i < qnt; i++) { // selection sort entre os elementos
        int index = i;

        for (int j = i; j < qnt; j++) {
            if((*elementos)[j] < (*elementos)[index]) index = j;
        }

        if (index != i) {
            (*elementos)[i] = (*elementos)[i] + (*elementos)[index];
            (*elementos)[index] = (*elementos)[i] - (*elementos)[index];
            (*elementos)[i] = (*elementos)[i] - (*elementos)[index];
        }
    }
}

int pesquisa(int **elementos, int init, int end, int chave) // função da pesquisa binária efetiva
{
    if (end >= init) { // confere se é possível continuar a busca
        int med = init + (end - init)/2; // calcula o ponto médio do array

        if ((*elementos)[med] == chave) return med; // caso o potno médio seja o valor pesquisado, o retorna
        if ((*elementos)[med] > chave) return pesquisa(elementos, init, med - 1, chave); // pesquisa abaixo do ponto médio caso a chave seja menor que esse
        else return pesquisa(elementos, med + 1, end, chave); // pesquisa acima do ponto médio em caso subjacente
    }

    return -1; // caso não seja possível pesquisar retorna -1
}

int main(void)
{
    int tam,        // variável do tamanho do vetor a ser inserido
        pesq,       // variável do valor a ser pesquisado
        *elementos; // variável do vetor númerico a ser lido

    scanf("%d %d", &tam, &pesq);         // lê o tamanho e a chave a ser pesquisada
    elementos = malloc(tam * sizeof(int)); // aloca o vetor dinamicamente

    leElementos(&elementos, tam);     // lê os elementos do vetor
    ordenaElementos(&elementos, tam); // orderna os elementos do vetor

    int res = pesquisa(&elementos, 0, tam - 1, pesq); // lê o retorno da pesquisa

    if (res > -1) printf("%d\n", res);  // exibe a a posição da chave pesquisada no vetor
    else printf("Chave inexistente\n"); // exibe a mensagem de erro caso não tenha sido possível encontrá-la

    free(elementos); // libera a memória do vetor

    return 0;
}