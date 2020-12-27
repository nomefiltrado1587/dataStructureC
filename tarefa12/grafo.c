#include "lista.h"
#include "grafo.h" 
#include <stdlib.h>

void adicionar_dependencia(p_grafo planilha,int posicao, int numero_do_vertice,int sinal){
    // CRIA UMA RELAÇÃO ENTRE DUAS CELULAS DA PLANILHA
    // UMA DELAS VIRA PAI DA OUTRA E A OUTRA VIRA FILHO
    planilha->vertices[posicao].pais = inserir_na_lista(planilha->vertices[posicao].pais,numero_do_vertice,sinal);
    planilha->vertices[numero_do_vertice].filhos = inserir_na_lista(planilha->vertices[numero_do_vertice].filhos,posicao,sinal);
}

int eh_dependente(p_grafo planilha, int vertice1, int vertice2){
    // DEFINE SE UMA CÉLULA E DEPENDENTE (FILHA) DA OUTRA
    p_lista lista = planilha->vertices[vertice1].pais;
    while(lista != NULL){
        if (lista->vertice == vertice2){
            return 1;
        }
        lista = lista->prox;
    }
    return 0;
}

Grafo inicializar_grafo(int total_de_termos,int largura){
    // INICIALIZA UM GRAFO
    Grafo grafo;
    grafo.largura = largura;
    grafo.total_termos = total_de_termos;
    grafo.vertices = malloc(total_de_termos*sizeof(Vertice));
    for (int i = 0;i< total_de_termos;i++){
        grafo.vertices[i].valor = 0;
        grafo.vertices[i].pais = NULL;
        grafo.vertices[i].filhos = NULL;
    }
    return grafo;
}

void liberar_grafo(p_grafo grafo){
    // LIBERA UM GRAFO
    p_lista aux,prox;
    for(int i = 0;i< grafo->total_termos;i++){
        aux = grafo->vertices[i].filhos;
        while(aux != NULL){
            prox = aux->prox;
            free(aux);
            aux = prox;
        }
        aux = grafo->vertices[i].pais;
        while(aux != NULL){
            prox = aux->prox;
            free(aux);
            aux = prox;
        }
    }
    free(grafo->vertices);
}