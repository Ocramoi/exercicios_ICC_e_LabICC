RUNNER=gcc
DAT_FOLDER=./Data/
SAIDA_INVERTE=Inversao.txt
SAIDA_BUBBLE=Bubble.txt

all: inverte bubble
	@for f in $(shell ls ${DAT_FOLDER}); do ./inverte $(DAT_FOLDER)$${f} >> $(SAIDA_INVERTE); done
	@for f in $(shell ls ${DAT_FOLDER}); do ./bubble $(DAT_FOLDER)$${f} >> $(SAIDA_BUBBLE); done

gera: adicionais
	./adicionais

adicionais:
	gcc adicionais.c -o adicionais

inverte:
	$(RUNNER) inverte.c -o inverte

bubble:
	$(RUNNER) bubble.c -o bubble

runInverte: inverte
	@for f in $(shell ls ${DAT_FOLDER}); do ./inverte $(DAT_FOLDER)$${f} >> $(SAIDA_INVERTE); done

runBubble: bubble
	@for f in $(shell ls ${DAT_FOLDER}); do ./bubble $(DAT_FOLDER)$${f} >> $(SAIDA_BUBBLE); done

clear:
	rm $(SAIDA_BUBBLE) $(SAIDA_INVERTE) bubble inverte adicionais