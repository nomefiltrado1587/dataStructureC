CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: planilha

caminho: planilha.c
	gcc $(CFLAGS) *.c -o planilha $(LDFLAGS)

clean:
	rm -f planilha
