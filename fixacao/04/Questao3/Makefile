all: cliente

cliente: cliente.o tintas.o
	gcc cliente.o tintas.o -lm -o cliente

cliente.o: cliente.c tintas.h
	gcc -std=c99 -Wall -Werror -c cliente.c

tintas.o: tintas.c tintas.h
	gcc -std=c99 -Wall -Werror -c tintas.c
