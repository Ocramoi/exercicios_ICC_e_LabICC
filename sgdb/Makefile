all:
	gcc sgbd.c -o sgbd -g

run:
	./sgbd

remove:
	rm registros.reg registros.idx

debug:
	valgrind --leak-check=yes ./sgbd