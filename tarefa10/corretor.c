#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_PALAVRAS 100
#define MAX_PALAVRA 25
#define LETRAS_ALFABETO 26

typedef struct No{
    char palavra[MAX_PALAVRA];
    struct No *prox;
}No;

typedef No *p_no;

typedef struct Hash{
    p_no palavras[100];
}Hash;


Hash inicializar_hash(){
    Hash novo;
    for (int i = 0;i<MAX_PALAVRAS;i++){
        novo->palavras[i] = NULL;
    }
}

p_no inserir_na_lista(char * palavra,p_no no){
    while(no!= NULL){
        no = no->prox;
    }
    novo = malloc(sizeof(No));
    novo->palavra = palavra;
    novo->prox = NULL;
    return novo;
}

int index(char *palavra){
    double index = 0;
    for (int i = 0;palavra[i] != '\0';i++){
        index += (int)palavra[i];
    }
    index = index*(sqtr(5)-1)/2;
    index = index%1;
    index = (MAX_PALAVRAS*index)/1;
    return index;
}

void inserir_no_hash(char *palavra,Hash *hash){
    double index = index(palavra);
    hash->palavras[index] = inserir_na_lista(palavra,hash->palavras[index]);
}

int comparar_strings(char *str1,char *str2){
    // COMPARA SE DUAS STRINGS SAO IGUAIS
    int eh_igual = 1;
    int i;
    for (i = 0;str1[i] != '\0' && str2[i] != '\0';i++){
        if(str1[i] != str2[i]){
            eh_igual = 0;
        }
    }
    if(str1[i] != str2[i]){
        eh_igual = 0;
    }
    return eh_igual;
}

int procurar_na_lista(char *palavra,p_no no){
    achou = 0;
    while(no != NULL){
        achou = comparar_strings(no->palavra,palavra);
        no = no->prox;
    }
    return achou;
}

int procurar_no_hash(char * palavra,Hash *dicionario){
    int achou = 0;
    index = index(palavra);
    achou = procurar_na_lista(palavra,dicionario->palavras[index]);
    return achou;
}

int procurar_similares(char * palavra,Hash *dicionario){
    int achou = 0;
    for(int i = 0;palavra[i] != '\0';i++){
        for(int j = 0;j<LETRAS_ALFABETO;j++){
            palavra[i] = 'a' +(palavra[i] + 1-'a')%LETRAS_ALFABETO;
            achou = procurar_no_hash(palavra,dicionario->palavras[index]);
        }
    }
    return achou;
}

int main(){
    Hash dicionario = inicializar_hash;
    int n,q,achou;
    char palavra_atual[MAX_PALAVRA];
    scanf("%d %d", &n,&q);
    for(int i = 0;i<n;i++){
        scanf("%s",palavra_atual);
        inserir_no_hash(palavra_atual,&dicionario);
    }
    for(int j = 0;j<q;j++){
        scanf("%s",palavra_atual);
        achou = 0;
        achou = procurar_no_hash(palavra_atual,&dicionario);
        if (achou == 1){
            printf("verde\n");
        }else{
            for(int k = 0;k<LETRAS_ALFABETO;k++){
                achou = procurar_similares(palavra_atual,&dicionario);
            }
            if (achou == 1){
                printf("amarelo\n");
            }else{
                printf("vermelho\n");
            }
        }
    }
}