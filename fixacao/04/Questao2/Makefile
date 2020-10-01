all: unidade4_1

unidade4_1: unidade4_1.o poligono.o
	gcc unidade4_1.o poligono.o -lm -o unidade4_1

unidade4_1.o: unidade4_1.c poligono.h
	gcc -std=c99 -Wall -Werror -c unidade4_1.c

poligono.o: poligono.c poligono.h
	gcc -std=c99 -Wall -Werror -c poligono.
