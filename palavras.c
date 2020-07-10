#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* leLinha(int* tam); // declaração da função de leitura de string e seu tamanho

int main(int argc, char* argv[])
{
    int op, tam1, tam2; // inteiros auxiliares para a opção desejada e para o tamanho das strings
    char *str1, *str2; // strings lidas

    op = leLinha(&tam1)[0]- 48; // lê a opção desejada

    str1 = leLinha(&tam1); // lê a primeira string
    str2 = leLinha(&tam2); // lê a segunda string

    switch (op) // confere a opção desejada
    {
        case 1: // primeira opção
            printf("%c\n", (tam1 > tam2) ? '1' : (tam2 > tam1) ? '2' : '0'); // confere o tamanho e exibe a string correta
            break; // termina o caso
        case 2: // segunda opção
            {
                char res = '0'; // char de resposta (empate por padrão)
                for(int k = 0; k < tam1 || k < tam2; k++) // confere caracter por caracter em ambas as plavras até o final de uma delas
                {
                    if(k >= tam1 || k >= tam2) // confere se alcançado o final de uma das strings, sendo então todos seus caracteres iguais porém de menor tamanha (alfabeticamente anterior)
                    {
                        res = (tam1 < tam2) ? '1' : '2'; // guarda a string menor
                        break;
                    }
                    //conjunto de condicionais que confere se um dos caracters é menor alfabeticamente
                    if (tolower(str1[k]) < tolower(str2[k])) {
                        res = '1';
                        break;
                    } else if (tolower(str1[k]) > tolower(str2[k])) {
                        res = '2';
                        break;
                    }
                }
                printf("%c\n", res); // exibe a resposta correta
                break; // termina o caso
            }
        case 3: // terceira opção
            {
                int sum1 = 0, sum2 = 0; // inicia os valores das somas
                for(int k = 0; k < tam1; k++)
                {
                    sum1 += tolower(str1[k]) - 97; // soma o valor referente ao caracter
                }
                for(int k = 0; k < tam2; k++)
                {
                    sum2 += tolower(str2[k]) - 97; // soma o valor referente ao caracter
                }
                printf("%c\n", (sum1 > sum2) ? '1' : (sum1 < sum2) ? '2' : '0'); // exibe a string certa de acordo com a soma
                break; // termina o caso
            }
        case 4: // quarta opção
            {
                char rep; // valor a ser pesquisado
                scanf("%c", &rep); // recebe o valor a ser pesquisado
                int sum1 = 0, sum2 = 0; // contadores
                for(int k = 0; k < tam1; k++) // loop entre caracteres da primeira string
                {
                    if (tolower(str1[k]) == tolower(rep)) // confere pelo caracter pesquisado
                        sum1++; // soma ao contador
                }
                for(int k = 0; k < tam2; k++) // loop entre caracteres da primeira string
                {
                    if (tolower(str2[k]) == tolower(rep)) // confere pelo caracter pesquisado
                        sum2++; // soma ao contador
                }
                printf("%c\n", (sum1 > sum2) ? '1' : (sum1 < sum2) ? '2' : '0'); // exibe a string certa de acordo com o contador
                break; // termina o caso
            }
        case 5: // quinta opção
            {
                char r = '0'; // caracter de resposta (empate por padrão)
                char f; // caracter a ser conferido
                scanf("%c", &f); // lê o caracter a ser conferido
                int pos1 = -1, pos2 = -1; // posições do caracter desejado em cada string (inicializa em valor inalcançável)
                for(int k = 0; k < tam1; k++) // confere caracter por caracter na primeira string
                {
                    if(tolower(str1[k]) == tolower(f)) // confere o caracter desejado
                    {
                        pos1 = k; // salva a posição encontrada
                        break;
                    }
                }
                for(int k = 0; k < tam2; k++) // confere caracter por caracter na segunda string
                {
                    if(tolower(str2[k]) == tolower(f)) // confere o caracter desejado
                    {
                        pos2 = k; // salva a posição encontrada
                        break;
                    }
                }
                if(pos1 !=  -1 || pos2 != -1) // confere se o caracter foi encontrado em alguma das strings
                {
                    if(pos1 == -1) r = '2'; // se o caracter não foi encontrado na primeira string, considera a segunda
                    else if(pos2 == -1) r = '1'; // se o caracter não foi encontrado na segunda string, considera a primeira
                    else r = (pos1 < pos2) ? '1' : (pos1 > pos2) ? '2' : '0'; // se o caracter foi encontrado em ambas as strings, salva a string com a posição de menor valor
                }
                printf("%c\n", r); // exibe a string correta de acordo com a posição do caracter encontrado (ou não)
                break; // termina o caso
            }
        default:
            break;
    }
    return 0;
}

char* leLinha(int* tam) // definição da função que lê as strings e seu tamanho
{
    int len = 0; // inicializa o tamanho da string em 0
    int c; // caracter a ser lido
    char* str = NULL; // string a ser lida

    do // loop até final de linha lido
    {
        c = getc(stdin); // lê o próximo caracter no arquivo padrão de entrada
        str = (char*) realloc(str, len+1); // aumenta a string em um caracter
        str[len++] = c; // adiciona o caracter lido
    } while (c != '\n');

    str[len-1] = '\0'; // adiciona o final de linha à string
    *tam = len - 1; // salva o tamanho da string desconsiderando o final de linha

    fflush(stdin); // limpa o arquivo de entrada

    return str; // retorna a string lida
}