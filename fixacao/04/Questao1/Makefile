all: unidade4

unidade4: unidade4.o numero_complexo.o
	gcc unidade4.o numero_complexo.o -lm -o unidade4

unidade4.o: unidade4.c numero_complexo.h
	gcc -std=c99 -Wall -Werror -c unidade4.c

numero_complexo.o: numero_complexo.c numero_complexo.h
	gcc -std=c99 -Wall -Werror -c numero_complexo.c

