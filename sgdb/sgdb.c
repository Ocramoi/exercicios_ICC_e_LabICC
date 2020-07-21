#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 64 // buffer do realloc de string

typedef struct
{
    char *fileName;
    char *keyName;
    char *keyType;
} METADATA;


/**
 * Função de leitura da entrada com tratamento. 
 */ 
char *readLine (FILE* entrada) { // função que lê string com tratamento
    char *retorno = NULL; // inicializa o ponteiro da frase lida
    int cont = 0; // inicializa a varável que auxiliará o tratamento de tamanho

    do {
        if (cont % STR_BUFFER == 0) { // conferência do tamanho como próximo múltiplo do buffer
            retorno = (char* ) realloc(retorno, ((cont/STR_BUFFER + 1) * STR_BUFFER) * sizeof(char)); // aumenta o tamanho da string em função do buffer caso tenha ultrapassado um novo múltiplo, diminuindo o gasto computacional com realocação
        }
        retorno[cont] = fgetc(entrada); // lê novo caracter
        cont++; // atualiza o tamanho da string
    } while (retorno[cont-1] != '\n' && retorno[cont-1] != EOF); // repete até o final da leitura de string

    if (cont >= 2 && retorno[cont - 2] == '\r') { // confere pelo caracter de formatação '\r'
        retorno[cont - 2] = '\0'; // substitui o caracter por fim de string
        retorno = (char* ) realloc(retorno, (cont-1) * sizeof(char)); // diminui o tamanho da string em 1 caracter
    }
     else {
        retorno[cont-1] = '\0'; // formata a string com o caracter de final de string
        retorno = (char*) realloc(retorno, cont * sizeof(char)); // realoca o ponteiro da string para seu tamanho desconsiderando o buffer
    }

    return retorno;
}

/**
 * Divide a string a partir do delimitador [delim] e retorna o elemento [n] do vetor gerado
 */
char *nSplit(char *str, const char *delim, int n) 
{
    char *copia = calloc(strlen(str) + 1, sizeof(char)); strcpy(copia, str); // cria uma cópia da string recebida para tratamento
    char *temp = strtok(copia, delim), // inicializa a tokenização da string
         *retorno = NULL; // inicializa o retorno da função
    int elem = 0; // elemento do split

    if(n < 0) return retorno; // trata a passagem de elemento desejado
    
    while (temp != NULL) { // acha o elemento desejado
        if(++elem > n) break;
        temp = strtok(NULL, delim);
    }

    if (temp != NULL) { // trata o retorno se possível
        retorno = realloc(retorno, (strlen(temp) + 1) * sizeof(char));
        strcpy(retorno, temp);
    }

    free(copia); // libera memória auxiliar alocada

    return retorno;
}

int getFileSize(FILE *arquivo) // procede ao final do arquivo para achar seu tamanho
{
    int pos = ftell(arquivo),
        tamArquivo;

    fseek(arquivo, 0, SEEK_END); 
    tamArquivo = ftell(arquivo);

    fseek(arquivo, pos, SEEK_SET);

    return tamArquivo;    
}

int getRegSize(char **fields, int nFields) // calcula e retorna o tamanho da estrutura do registro
{
    int tamRegistro = sizeof(int); // inicializa o tamanho com o campo padrão de código
    for(int i = 1; i <= nFields; i++) { // para cada campo soma o tamanho correto
        if(!strcmp(nSplit(fields[1 + (i-1)*2], "[", 0), "char")) {
            tamRegistro += atoi(nSplit(nSplit(fields[1 + (i-1)*2], "[", 1), "]", 0)) * sizeof(char);
        }
        else if (!strcmp(fields[1 + (i-1)*2], "double")) tamRegistro += sizeof(double);
        else if (!strcmp(fields[1 + (i-1)*2], "float")) tamRegistro += sizeof(float);
        else if (!strcmp(fields[1 + (i-1)*2], "int")) tamRegistro += sizeof(int);
    }

    return tamRegistro;
}

void insert(char **fields, int nFields, char *comando, METADATA meta, FILE *arqSaida) // insere registro no arquivo a partir do comando
{
    if (!strcmp(meta.keyType, "int")) { // armazena a chave com tipo correto
        int index = atoi(nSplit(nSplit(comando, ",", 0), " ", 1));
        fwrite(&index, sizeof(int), 1, arqSaida);
    }
    else if (!strcmp(meta.keyType, "double")) {
        double index = atof(nSplit(nSplit(comando, ",", 0), " ", 1));
        fwrite(&index, sizeof(double), 1, arqSaida);
    }
    else if (!strcmp(meta.keyType, "float")) {
        float index = (float) atof(nSplit(nSplit(comando, ",", 0), " ", 1));
        fwrite(&index, sizeof(float), 1, arqSaida);
    }

    for (int i = 0; i < nFields; i++) // escreve os parâmetros do comando a partir do tipo de campo
    {
        if(!strcmp(nSplit(fields[i*2 + 1], "[", 0), "char")) {
            int tamEscrita = atoi(nSplit(nSplit(fields[i*2 + 1], "[", 1), "]", 0));
            char *escrita = calloc(tamEscrita, sizeof(char));
            strcpy(escrita, nSplit(nSplit(comando, ",", i + 1), "\"", 1));
            fwrite(escrita, sizeof(char), tamEscrita * sizeof(char), arqSaida);
            free(escrita);
        }
        else if (!strcmp(fields[i*2 + 1], "double")) {
            double escrita = atof(nSplit(comando, ",", i + 1));
            fwrite(&escrita, sizeof(double), 1, arqSaida);
        }
        else if (!strcmp(fields[i*2 + 1], "float")) {
            float escrita = (float) atof(nSplit(comando, ",", i + 1));
            fwrite(&escrita, sizeof(float), 1, arqSaida);
        }
        else if (!strcmp(fields[i*2 + 1], "int")) {
            int escrita = atoi(nSplit(comando, ",", i + 1));
            fwrite(&escrita, sizeof(int), 1, arqSaida);
        }
    }
}

void _index(char **fields, int nFields, METADATA meta, FILE *arquivo) // gera o arquivo de indexação ordenada
{
    long pos = ftell(arquivo), // posição atual do cursor no arquivo
         tamArquivo = getFileSize(arquivo),
         tamRegistro = getRegSize(fields, nFields),
         nRegistros = tamArquivo/tamRegistro; // obtem o número de registros a partir do tamanho da arquivo e do tamanho de cada registro

    int *posicoes = malloc(nRegistros*sizeof(int));
    for (int i = 0; i < nRegistros; i++) posicoes[i] = i*tamRegistro; // cria lista de índices de posição dos registros no arquivo

    int *iRegis = NULL;
    float *fRegis = NULL;
    double *dRegis = NULL; // cria variáveis para alocação do tipo necessário de valor

    if (!strcmp(meta.keyType, "int")) { // cria lista de códigos do tipo correto
        iRegis = malloc(nRegistros*sizeof(int));
        for(int i = 0; i < nRegistros; i++) {
            fseek(arquivo, i*tamRegistro, SEEK_SET);
            fread(&iRegis[i], sizeof(int), 1, arquivo);
        }
    }
    else if (!strcmp(meta.keyType, "double")) {
        dRegis = malloc(nRegistros*sizeof(double));
        for(int i = 0; i < nRegistros; i++) {
            fseek(arquivo, i*tamRegistro, SEEK_SET);
            fread(&dRegis[i], sizeof(double), 1, arquivo);
        }
    }
    else if (!strcmp(meta.keyType, "float")) {
        fRegis = malloc(nRegistros*sizeof(float));
        for(int i = 0; i < nRegistros; i++) {
            fseek(arquivo, i*tamRegistro, SEEK_SET);
            fread(&fRegis[i], sizeof(float), 1, arquivo);
        }
    }

    for (int i = 0; i < nRegistros; i++) { // selection sort entre os registros e códigos indexados (tratando ambos os campos)
        int index = i;

        for (int j = i; j < nRegistros; j++) {
            if (iRegis && iRegis[j] < iRegis[index]) index = j;
            else if (fRegis && fRegis[j] < fRegis[index]) index = j;
            else if (dRegis && dRegis[j] < dRegis[index]) index = j;
        }
        
        if (index != i) {
            posicoes[i] = posicoes[i] + posicoes[index];
            posicoes[index] = posicoes[i] - posicoes[index];
            posicoes[i] = posicoes[i] - posicoes[index];

            if (iRegis) {
                iRegis[i] = iRegis[i] + iRegis[index];
                iRegis[index] = iRegis[i] - iRegis[index];
                iRegis[i] = iRegis[i] - iRegis[index];
            } else if (fRegis) {
                fRegis[i] = fRegis[i] + fRegis[index];
                fRegis[index] = fRegis[i] - fRegis[index];
                fRegis[i] = fRegis[i] - fRegis[index];
            } else if (dRegis) {
                dRegis[i] = dRegis[i] + dRegis[index];
                dRegis[index] = dRegis[i] - dRegis[index];
                dRegis[i] = dRegis[i] - dRegis[index];
            }
        }
    }

    FILE *idx = fopen("registros.idx", "w"); // salva registros para o arquivo de indexação
    for (int i = 0; i < nRegistros; i++) {
        if (iRegis) fwrite(&iRegis[i], sizeof(int), 1, idx);
        else if (dRegis) fwrite(&dRegis[i], sizeof(double), 1, idx);
        else if (fRegis) fwrite(&fRegis[i], sizeof(float), 1, idx);
        fwrite(&posicoes[i], sizeof(int), 1, idx);
    }
    fclose(idx); // fecha arquivo de indexação

    fseek(arquivo, pos, SEEK_SET); // retorna cursor do arquivo
}

int regBinarySearch(int *regis, int start, int end, int key) // busca binária recursiva dos registros retornando sua posição
{
    if (end >= start) {
        int mid = start + (end - start)/2;

        // realiza a busca com os índices e retorna o elemento posterior, sua posição
        if (regis[mid*2] == key)
            return regis[mid*2 + 1];

        if (regis[mid*2] > key)
            return regBinarySearch(regis, start, mid-1, key);

        if(regis[mid*2] < key)
            return regBinarySearch(regis, mid+1, end, key);
    }

    return -1; // retorno em caso de falha na pesquisa
}

void search(char **fields, int nFields, FILE *arquivo, int key, METADATA meta)
{
    _index(fields, nFields, meta, arquivo);
    FILE *registros = fopen("registros.idx", "r"); // cria o arquivo de indexação e o abre para busca  

    int numRegistros = getFileSize(registros)/(2*sizeof(int)), // calcula o número de registros no arquivo
        *regis = calloc(numRegistros*2, sizeof(int)),          // inicializa o vetor de registros
        pos = ftell(arquivo);                                  // registra a posição atual do cursor no arquivo

    fread(regis, sizeof(int), numRegistros*2, registros); // salva os registros no vetor
    fclose(registros); // fecha o arquivo, agora já copiado

    int correto = regBinarySearch(regis, 0, numRegistros, key); // faz a pesquisa binária pelo índice
    if (correto > -1) { // caso tenha encontrado o registro
        // posiciona o cursor na posição correta do arquivo e lê e exibe seus campos
        fseek(arquivo, correto, SEEK_SET);
        
        printf("%s: ", meta.keyName);
        if (!strcmp(meta.keyType, "int")) { // exibe o tipo correto de chave
            int index; fread(&index, sizeof(int), 1, arquivo);
            printf("%d\n", index);
        }
        else if (!strcmp(meta.keyType, "double")) {
            double index; fread(&index, sizeof(double), 1, arquivo);
            printf("%lf\n", index);
        }
        else if (!strcmp(meta.keyType, "float")) {
            float index; fread(&index, sizeof(float), 1, arquivo);
            printf("%f\n", index);
        }
        
        for (int i = 0; i < nFields; i++) // exibe os campos de registro de acordo com tipo
        {
            printf("%s: ", fields[i*2]);
            if(!strcmp(nSplit(fields[i*2 + 1], "[", 0), "char")) {
                int tamString = atoi(nSplit(nSplit(fields[i*2 + 1], "[", 1), "]", 0));
                char *campo = calloc(tamString, sizeof(char));
                fread(campo, sizeof(char), tamString, arquivo);
                printf("%s\n", campo);
                free(campo);
            }
            else if (!strcmp(fields[i*2 + 1], "double")) {
                double campo;
                fread(&campo, sizeof(double), 1, arquivo);
                printf("%.2lf\n", campo);
            }
            else if (!strcmp(fields[i*2 + 1], "float")) {
                float campo;
                fread(&campo, sizeof(float), 1, arquivo);
                printf("%.2f\n", campo);
            }
            else if (!strcmp(fields[i*2 + 1], "int")) {
                int campo;
                fread(&campo, sizeof(int), 1, arquivo);
                printf("%d\n", campo);
            }
        }
        printf("\n");
    }

    fseek(arquivo, pos, SEEK_SET); // retorna o cursor do arquivo para a posição inicial
}

int main(void)
{
    char *nomeArqMeta = readLine(stdin);
    FILE *arqMeta = fopen(nomeArqMeta, "r"); // abre o arquivo digitado

    // lê os metadatos padrão (nome do arquivo de arquivo e propriedades do índice)
    METADATA mData;
    mData.fileName = nSplit(readLine(arqMeta), ": ", 1);
    mData.keyName  = nSplit(readLine(arqMeta), ": ", 1);
    mData.keyType  = nSplit(readLine(arqMeta), ": ", 1);
    
    char **fields = NULL;
    int nFields = 0; // variáveis da lista de campos [metadados]

    char *field1 = NULL, *field2 = NULL;
    do {  // leitura campo a campo dos metadados
        free(field1); free(field2);
        field1 = readLine(arqMeta), field2 = readLine(arqMeta);

        if(strlen(field1) <= 0) break;

        fields = realloc(fields, ++nFields * 2 * sizeof(char *));
        fields[(nFields - 1) * 2 + 0] = nSplit(field1, ": ", 1);
        fields[(nFields - 1) * 2 + 1] = nSplit(field2, ": ", 1);
    } while (strlen(field1) > 0);
    free(field1); free(field2); // libera variáveis auxiliares

    FILE *arqSaida = fopen(mData.fileName, "a+"); // abre arquivo de saída para acréscimo de dados e leitura

    char *comando = NULL,
         *op; // variáveis para leitura dos comandos digitados
    do {
        free(comando);
        comando = readLine(stdin); // lê o novo comando
        
        op = nSplit(comando, " ", 0); // lê a opção de operação
        
        // realiza a operação digitadas
        if(!strcmp(op, "exit")) break;
        else if (!strcmp(op, "insert")) { insert(fields, nFields, comando, mData, arqSaida); }
        else if (!strcmp(op, "index")) _index(fields, nFields, mData, arqSaida);
        else if (!strcmp(op, "search")) search(fields, nFields, arqSaida, atoi(nSplit(comando, " ", 1)), mData);
    } while (strcmp(op, "exit"));

    // libera vetor de campos
    for(int i = 0; i < nFields * 2; i++) 
        free(fields[i]);
    free(fields);

    fclose(arqMeta); fclose(arqSaida); // fecha arquivos abertos
    free(op); free(comando); free(nomeArqMeta); free(mData.fileName); free(mData.keyName); free(mData.keyType); // libera memória alocada

    return 0;
}