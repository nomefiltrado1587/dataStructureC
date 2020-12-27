#include "lista.h"
#include <stdlib.h>

p_lista inserir_na_lista(p_lista lista,int elemento, int sinal){
    // INSERE UM VERTICE EM UMA LISTA DE DEPENDENCIAS
    // CASO ELE JA ESTEJA NELA, É APENAS ACRESCENTADO O SINAL

    p_lista aux = lista;
    while(aux != NULL){
        if(aux->vertice == elemento){
            aux->dependencia += sinal;
            return lista;
        }
        aux = aux->prox;
    }
    p_lista novo = malloc(sizeof(Lista));
    novo->vertice = elemento;
    novo->dependencia = sinal;
    novo->prox = lista;
    return novo;
}