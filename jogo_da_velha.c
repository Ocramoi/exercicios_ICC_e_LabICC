#include <stdio.h>
#include <stdlib.h>

char confereJogo(char* tab); // declaração da função que confere se algum jogador venceu o jogo nessa jogada
void exibeMatriz(char* tab); // declaração da função que exibe todas as casas do jogo e seus valores

int main(void)
{
    char* jogo = (char*) malloc(9 * sizeof(char)); // matriz referente às posiçoes do jogo
    int loc; // variável de armazenamento da localização desejada pelo jogador
    for(int k = 0; k < 9; k++) // completa o jogo com as posições
    {
        jogo[k] = (char) (49 + k);
    }
    exibeMatriz(jogo); // exibe o jogo
    printf("Jogo da velha!\n");
    char conf = '!'; // inicializa char que confere se algum jogador venceu
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < 2; i++)
        {
            if(i == 1 && k == 4) break; // confere se todas as posições já foram jogadas
            printf("Escolha um número para jogar, jogador %c!\n",
                    (i == 0) ? 'X': 'O'); // prompt do jogador
            do
            {
                scanf("%d", &loc); // lê a localização desejada
                if(jogo[loc-1] == 'X' || jogo[loc-1] == 'O') // checa se a posição está ocupada
                {
                    printf("Jogada inválida! Escolha outra casa.\n"); // prompt de erro
                }
            } while (jogo[loc-1] == 'X' || jogo[loc-1] == 'O'); // confere se houve erro na jogada
            jogo[loc-1] = (i == 0) ? 'X' : 'O'; // registra a jogada
            exibeMatriz(jogo); // exibe o jogo
            conf = confereJogo(jogo); // passa para o char de conferência o estado do jogo
            if(conf != '.') // se um dos jogadores venceu nessa jogada
            {
                k = 10; // quebra o loop exterior
                break; // quebra o loop interior
            }
        }
    }
    if(conf == '.') // confere se ao final das jogadas não há vencedores
    {
        printf("Deu velha!\n"); // prompt de "velha"
    } else { // caso haja vencedor
        printf("Fim do jogo! O jogador %c venceu!\n", conf); // exibe o vencedor
    }
    free(jogo); // libera memória alocada para as posições do jogo
    return 0;
}

char confereJogo(char* tab) // definição da função que confere se algum jogador venceu o jogo nessa jogada => . -> sem vencedor, X -> X vence, O -> O vence
{
    for(int k = 0; k < 3; k++)
    {
        if(tab[(k*3)] == tab[(k*3) + 1] &&
           tab[(k*3) + 1] == tab[(k*3) + 2]) // confere para cada linha se uma delas foi completa por um jogador
        {
            return tab[k*3]; // retorna o vencedor
        }
        if(tab[k] == tab[k+3] &&
           tab[k+3] == tab[k+6])  // confere para cada coluna se uma delas foi completa por um jogador
        {
            return tab[k]; // retorna o vencedor
        }
    }
    if((tab[0] == tab[4] &&
       tab[4] == tab[8]) ||
       (tab[2] == tab[4] &&
        tab[4] == tab[6])) // confere para cada diagonal se uma delas foi completa por um jogador
    {
        return tab[4]; // retorna o vencedor
    }
    return '.'; // retorno caso não haja vencedores
}

void exibeMatriz(char* tab) // definição da função que exibe todas as casas do jogo e seus valores
{
    for(int k = 0; k < 9; k+=3)
    {
        for (int i = 0; i < 3; i++) {
            printf("%c   |", tab[k+i]); // exibe cada valor seguido de '   |'
        }
        printf("\n----+----+-----\n"); // exibe a divisão de linhas
    }
}