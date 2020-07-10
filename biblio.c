#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 2048 // buffer do realloc de string

typedef struct {
    char *nome;
    int max_dias;
} LIVRO; // estrutura que representa cada livro, com seu nome e tempo apra devolução

char *leFrase() { // função que lê string com tratamento
    char *retorno = NULL; // inicializa o ponteiro da frase lida
    int cont = 0; // inicializa a varável que auxiliará o tratamento de tamanho

    do {
        if (cont % STR_BUFFER == 0) { // conferência do tamanho como próximo múltiplo do buffer
            retorno = (char* ) realloc(retorno, ((cont/STR_BUFFER + 1) * STR_BUFFER) * sizeof(char)); // aumenta o tamanho da string em função do buffer caso tenha ultrapassado um novo múltiplo, diminuindo o gasto computacional com realocação
        }
        retorno[cont] = fgetc(stdin); // lê novo caracter
        cont++; // atualiza o tamanho da string
    } while (retorno[cont-1] != '\n' && retorno[cont-1] != EOF); // repete até o final da leitura de string

    if (cont >= 2 && retorno[cont - 2] == '\r') { // confere pelo caracter de formatação '/r'
        retorno[cont - 2] = '\0'; // substitui o caracter por fim de string
        retorno = (char* ) realloc(retorno, (cont-1) * sizeof(char)); // diminui o tamanho da string em 1 caracter
    }
    else {
        retorno[cont-1] = '\0'; // formata a string com o caracter de final de string
        retorno = (char* ) realloc(retorno, cont * sizeof(char)); // realoca o ponteiro da string para seu tamanho desconsiderando o buffer
    }
    return retorno; // retorna a string lida
}

char confereLivro(LIVRO* livros, int n_livros, char* pesquisa) // função para confer^ncia do livro dentro de um vetor
{
    char retorno = 0; // inicializa a opção de retorno como falsa
    for(int k = 0; k < n_livros; k++) // loop por todos os elementos
    {
        if(!strcmp(livros[k].nome, pesquisa))
        {
            return 1; // retorna verdadeiro caso o atual elemento da lista seja igual a pesquisa
        }
    }
    return retorno; // retorna falso caso não tenha achado o livro pesquisado
}

int main(void)
{
    int n_livros, n_alugados = 0; // inicializa as variáveis para o tamanho da lsita de livros total e alugados
    n_livros = atoi(leFrase()); // lê o total de livros a serem inseridos

    LIVRO *livros = (LIVRO*) malloc(n_livros * sizeof(LIVRO)), // inicializa o vetor de livros total em função do númeor de livros a serem lidos
          *alugados = NULL; // inicializa o vetor de livros alugados

    for(int k= 0; k < n_livros; k++) // lê o nome e número máximo de dias para aluguel de todos os livros
    {
        livros[k].nome = leFrase();
        livros[k].max_dias = atoi(leFrase());
    }

    char op; // variável para leitura da opção desejada
    do {
        op = atoi(leFrase()); // lê a opção desejada

        switch (op) { // confere a opção desejada
            case 1:
                {
                    printf("Digite o livro que voce procura:\n");
                    char *pesquisa = leFrase(); // lê o livro a ser pesquisada para aluguel
                    for(int k = 0; k < n_livros; k++) // loop por todos os livros
                    {
                        if(!strcmp(livros[k].nome, pesquisa)) // confere se o item atual é o pesquisado
                        {
                            if(n_alugados >= 10) { // cancela a operação caso o usúario tenha 10 livros alugados
                                printf("Voce ja tem 10 livros alugados\n");
                                break;
                            }
                            if (confereLivro(alugados, n_alugados, pesquisa)) // cancela a operação caso o usúario já tenha alugado o livro
                            {
                                printf("Livro ja alugado\n");
                                break;
                            }
                            alugados = (LIVRO*) realloc(alugados, ++n_alugados * sizeof(LIVRO)); // incrementa o número de livros alugados em 1
                            alugados[n_alugados-1].nome = livros[k].nome;           // configura o livro alugado
                            alugados[n_alugados-1].max_dias = livros[k].max_dias;
                            printf("%s alugado com sucesso\n", livros[k].nome); // mensagem de sucesso
                            break;
                        } else if(k == n_livros - 1)
                            printf("Livro nao encontrado na biblioteca\n"); // mensagem caso o çivro não seja encontrado
                    }
                    break;
                }
            case 2:
                {
                    if(n_alugados == 0)
                    {
                        printf("Voce nao tem livros alugados\n"); // mensagem caso o usuário não tenha alugado nenhum livro
                        break;
                    }
                    printf("Voce tem %d livro(s) alugado(s)\n", n_alugados); // exibe a quantidade de livros alugados
                    for(int k = 0; k < n_alugados; k++)
                    {
                        printf("Livro nome: %s\nDevolve-lo daqui %d dias\n", alugados[k].nome, alugados[k].max_dias); // exibe as informações de cada livro
                    }
                    break;
                }
            case 3:
                {
                    printf("Digite o livro que deseja devolver:\n");
                    char *pesquisa = leFrase(),  // lê o livro a ser pesquisada para devolução
                         encontrado = 0; // flag caso o livro esteja atualmente alugado
                    for(int k = 0; k < n_alugados; k++) // loop entre os livros alugados
                    {
                        if(!strcmp(alugados[k].nome, pesquisa)) // confere se o item atual é o pesquisado
                        {
                            int cont = 0; // variável de contagem para o novo vetor sem o item a ser devolvido
                            for(int l = 0; l < n_alugados; l++) // loop entre todos os livros alugados
                            {
                                if(strcmp(alugados[l].nome, pesquisa) != 0)
                                {
                                    alugados[cont] = alugados[l]; // mantém todos os livros que não aquele a ser devolvido
                                    cont++;
                                }
                            }
                            alugados = (LIVRO*) realloc(alugados, (--n_alugados) * sizeof(LIVRO)); // atualiza o tamanho do vetor de livros alugados (sem o devolvido)
                            printf("Livro %s foi devolvido com sucesso\n", pesquisa); // mensagem em relação ao livro devolvido
                            encontrado = 1; // atulaiza a flag caso tenha sido devolvido
                            break;
                        }
                    }
                    if(!encontrado)
                        printf("Voce nao possui esse livro\n"); // mensagem caso o livro não tenha sido devolvido (não estava na lista de livros alugados)
                    break;
                }
            default:
                break;
        }
    } while (op != 4);

    printf("Programa finalizado\n"); // mensagem de finalização do programa

    free(livros); // libera o ponteiro de livros total
    free(alugados); // libera o ponteiro de livros alugados

    return 0;
}