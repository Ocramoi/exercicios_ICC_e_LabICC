COMPILER=gcc # compilador selecionado
SAIDA=main   # nome do executável de saída

all: main.o
	$(COMPILER) main.o -o $(SAIDA)

run:
	./$(SAIDA)

main.o: main.c