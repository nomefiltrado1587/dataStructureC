#include <stdio.h>
#include <stdlib.h>
#define MAX_NOME 50
#define MAX_TIPO 15

typedef struct Paciente{
    char nome[50];
    p_no atendimentos;
}

typedef struct No{
    int dado;
    struct No *prox;
}No;

typedef struct No *p_no;

p_no adicionar_normal(p_no final_fila,Paciente paciente){

}


int main(){

    char nome[MAX_NOME],tipo[MAX_TIPO];
    char aux,letra;
    int i;
    p_no inicio_fila;
    p_no final_fila;
    scanf(" %c",&aux);
        do{
        for(i = 0;i<MAX_NOME-1 && letra != '"';i++){
            scanf(" %c",&letra);
            nome[i] = letra;
        }
        nome[i+1] = '\0';
        scanf(" %s",tipo);

        

        scanf(" %c",&aux);
    }while(aux == '"');
}