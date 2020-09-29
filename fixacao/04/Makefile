all: unidade4 unidade4_1

unidade4: unidade4.o numero_complexo.o
	gcc unidade4.o numero_complexo.o -lm -o unidade4

unidade4.o: unidade4.c numero_complexo.h
	gcc -std=c99 -Wall -Werror -c unidade4.c

numero_complexo.o: numero_complexo.c numero_complexo.h
	gcc -std=c99 -Wall -Werror -c numero_complexo.c

unidade4_1: unidade4_1.o poligono.o
	gcc unidade4_1.o poligono.o -lm -o unidade4_1

unidade4_1.o: unidade4_1.c poligono.h
	gcc -std=c99 -Wall -Werror -c unidade4_1.c

poligono.o: poligono.c poligono.h
	gcc -std=c99 -Wall -Werror -c poligono.c
