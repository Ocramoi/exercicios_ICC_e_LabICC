#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_STR 64	// tamanho do buffer de leitura do nome do arquivo
#define INIT_PALETA 54	// ponto de início da paleta de cores

void editaValores(unsigned char *R, unsigned char *G, unsigned char *B, int op) // função de alteração dos valores da paleta para a opção desejada
{
	if(op == 1) { // tratamento caso negativo
		*R = abs((int)*R - 255); 
		*G = abs((int)*G - 255);
		*B = abs((int)*B - 255);
	} else { // tratamento de greyscale
		int greyScale = (*R + *G + *B)/3;
		*R = greyScale; 
		*G = greyScale;
		*B = greyScale;
	}
}

int main(void)
{ 
	char *nomeArquivo = malloc(BUFFER_STR * sizeof(char)); // leitura do nome do arquivo inserido
	// leitura do nome de arquivo
	fgets(nomeArquivo, BUFFER_STR, stdin);
	nomeArquivo[strlen(nomeArquivo) - 1] = '\0';
	nomeArquivo = realloc(nomeArquivo, (strlen(nomeArquivo) + 1) * sizeof(char));

	int op; scanf("%d", &op); // leitura da opção de tratamento

	FILE *arquivo = fopen(nomeArquivo, "rb"); // abertura do arquivo inserido

	if(arquivo == NULL) { // tratamento caso erro de arquivo não existente
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		free(nomeArquivo);
		fclose(arquivo);
		return 1;
	}
	// tratamento de conferência do formato BMP
	fseek(arquivo, 0, SEEK_SET);	
	if((nomeArquivo[strlen(nomeArquivo) - 3] != 'b' || nomeArquivo[strlen(nomeArquivo) - 2] != 'm' || nomeArquivo[strlen(nomeArquivo) - 1] != 'p') || (fgetc(arquivo) != 'B' || fgetc(arquivo) != 'M')) printf("Arquivo nao eh formato BMP\n");

	// tratamento do nome do arquivo de saída
	char *nomeSaida = malloc((strlen(nomeArquivo) + ((op == 1) ? 8 : 11) + 1) * sizeof(char));
	strncpy(nomeSaida, nomeArquivo, strlen(nomeArquivo) - 4);                                       	
	strcpy(nomeSaida + strlen(nomeArquivo) - 4, (op == 1) ? "Negativo.bmp\0" : "PretoBranco.bmp\0");
	FILE *saida = fopen(nomeSaida, "wb"); // criação do ponteiro do arquivo de saída

	// leitura do tamawnho do arquivo
	fseek(arquivo, 2, SEEK_SET);
	unsigned int tamanhoArq = 0;
    tamanhoArq += fgetc(arquivo);
	tamanhoArq += fgetc(arquivo) * 256;
	tamanhoArq += fgetc(arquivo) * 256 * 256;
	tamanhoArq += fgetc(arquivo) * 256 * 256 * 256;
		
	unsigned char *imgEditada = malloc(tamanhoArq * sizeof(unsigned char)), // array representativo da imagem editada byte a byte
				  *paletaOriginal = malloc(256 * 3 * sizeof(char));			// array da paleta original
	
	fseek(arquivo, 0, SEEK_SET);
	for(int i = 0; i < tamanhoArq; i++) imgEditada[i] = fgetc(arquivo); // cópia da imagem original inciialmente à imagem editada
	
	for(int i = 0; i < 256; i++) {
		paletaOriginal[i*3 + 0] = imgEditada[INIT_PALETA + i*4 + 0];
		paletaOriginal[i*3 + 1] = imgEditada[INIT_PALETA + i*4 + 1];
		paletaOriginal[i*3 + 2] = imgEditada[INIT_PALETA + i*4 + 2]; // geração do array de paleta original
		
		editaValores(&imgEditada[INIT_PALETA + i*4], &imgEditada[INIT_PALETA + i*4 + 1], &imgEditada[INIT_PALETA + i*4 + 2], op); // edita os valores da paleta da imagem editada
	}

	for(int i = 0; i < tamanhoArq; i++)
		fprintf(saida, "%c", imgEditada[i]); // arquivamento da imagem editada
	
	// exibição das propriedades da imagem
	fseek(arquivo, 0, SEEK_SET);
	printf("CABEÇALHO:\n");
	char ini1 = fgetc(arquivo), ini2 = fgetc(arquivo);
	printf("Iniciais: %c%c\n", ini2, ini1);
	printf("Tamanho do arquivo: %u\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Reservado: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Deslocamento, em bytes, para o inicio da area de dados: %u\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Tamanho em bytes do segundo cabecalho: %u\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	int largura = fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256,
		altura = fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256; // leitura da largura e altura da imagem para uso futuro
	printf("Resoluçao: %d x %d\n", largura, altura);
	printf("Numero de planos: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256);
	printf("Bits por pixel: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256);
	printf("Compressao usada: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Tamanho imagem: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Resolucao horizontal: %d pixel por metro\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Resolucao Vertical: %d pixel por metro\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Numero de cores usadas: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);
	printf("Numero de cores importantes: %d\n", fgetc(arquivo) + fgetc(arquivo) * 256 + fgetc(arquivo) * 256 * 256 + fgetc(arquivo) * 256 * 256 * 256);

	printf("PALETA ORIGINAL:\n"); // exibição da paleta original
	for(int i = 0; i < 256; i++) printf("Paleta[%d]: R:%u G:%u B:%u\n", i, paletaOriginal[i*3 + 2], paletaOriginal[i*3 + 1], paletaOriginal[i*3]);

	printf("PALETA NOVA:\n"); // exibição da paleta editada
	for(int i = 0; i < 256; i++) printf("Paleta[%d]: R:%u G:%u B:%u\n", i, imgEditada[INIT_PALETA + i*4 + 2], imgEditada[INIT_PALETA + i*4 + 1], imgEditada[INIT_PALETA + i*4]);

	int larguraReal = ((int)(largura/4) * 4) + ((largura % 4 > 0) ? 4 : 0); // cálculo do número de pixels por linha sem o padding
	for (int i = altura - 1; i >= 0; i--) // exibe a soma de todas as linhas corrigidas para o padding
	{
		fseek(arquivo, 1078 + i * larguraReal, SEEK_SET);
		long long soma = 0;
		for (int j = 0; j < largura; j++) soma += fgetc(arquivo);
		printf("Soma linha %d: %lld\n", altura - 1 - i, soma - (larguraReal - largura));
	}

	printf("%s\n", nomeSaida); // exibição do nome de saída

	// libera ponteiros
	free(paletaOriginal);
	free(imgEditada);
	free(nomeArquivo);
	free(nomeSaida);
	fclose(arquivo);
	fclose(saida);

	return 0;
}
