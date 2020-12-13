#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertice {
    double x,y;
    struct Vertice *prox;
} Vertice;

typedef Vertice * p_vertice;

typedef struct Grafo{
    int **matriz_distancias;
    p_vertice *vertices;
    int n;
} Grafo;

typedef Grafo * p_grafo;

Grafo inicializar_grafo(){
    Grafo grafo;
    grafo.n = 0;
    grafo.matriz_distancias = NULL;
    grafo.vertices = NULL;
    return grafo;
}

void zerar_vetor(int *v,int n){
    for (int i = 0;i<n;i++){
        v[i] = 0;
    }
}

void receber_ponto_inicial(p_vertice inicio){
    double x_inicial,y_inicial;
    scanf(" %lf %lf", &x_inicial,&y_inicial);
    inicio->x = x_inicial;
    inicio->y = y_inicial;
    inicio->prox = NULL;
}

p_vertice adicionar_vertice(p_vertice lista,double x, double y){

    p_vertice novo = malloc(sizeof(Vertice));
    novo->x = x;
    novo->y = y;
    novo->prox =  lista;

    return novo;
}

void liberar_grafo(p_grafo grafo){
    for(int i = 0;i<grafo->n;i++){
        free(grafo->vertices[i]);
        free(grafo->matriz_distancias[i]);
    }
    free(grafo->vertices);
    free(grafo->matriz_distancias);

}

int distancia_inteira(p_vertice no1,p_vertice no2){
    double distancia = 0;
    distancia += (no1->x-no2->x)*(no1->x-no2->x);
    distancia += (no1->y-no2->y)*(no1->y-no2->y);
    distancia = sqrt(distancia);
    int resultado = (int)distancia;
    return resultado+1;
}

void armazenar_vertices_no_grafo(p_grafo grafo, p_vertice lista_de_vertices,int quantidade_de_vertices){
    grafo->n = quantidade_de_vertices;
    grafo->vertices = malloc(sizeof(p_vertice)*grafo->n);
    for(int i = 0;i<grafo->n;i++){
        grafo->vertices[i] = lista_de_vertices;
        lista_de_vertices = lista_de_vertices->prox;
    }
}

void criar_matriz_de_distancias(p_grafo grafo,int *aresta_min,int *aresta_max,int *aresta_atual){
    int i,j,n,distancia_atual;
    n = grafo->n;

    grafo->matriz_distancias = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++){
        grafo->matriz_distancias[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < i; j++){
            distancia_atual = distancia_inteira(grafo->vertices[i],grafo->vertices[j]);
            if(distancia_atual > *aresta_max){
                *aresta_max = distancia_atual;
            }
            if(distancia_atual < *aresta_min){
                *aresta_min = distancia_atual;
            }
            grafo->matriz_distancias[i][j] = distancia_atual;
            grafo->matriz_distancias[j][i] = distancia_atual;
        }
    }
    for (i = 0;i<n;i++){
        grafo->matriz_distancias[i][i] = 0;
    }
    *aresta_atual = (*aresta_max + *aresta_min)/2;
}

void receber_entrada(p_vertice *lista_de_vertices,p_vertice *lista_de_lugias,int *quantidade_de_vertices,int *quantidade_de_lugias){
    double x_atual,y_atual;
    char tipo[15];

    while (scanf(" %lf %lf %s",&x_atual,&y_atual,tipo) > 0){
        *quantidade_de_vertices += 1;
        if (tipo[0] == 'L'){
            *lista_de_lugias = adicionar_vertice(*lista_de_lugias,x_atual,y_atual);
            *quantidade_de_lugias += 1;
        }else{
            *lista_de_vertices = adicionar_vertice(*lista_de_vertices,x_atual,y_atual);
        }
    }
    p_vertice aux = *lista_de_lugias;
    int contador = 0;
    while(aux->prox != NULL){
        aux = aux->prox;
        contador += 1;
    }
    aux->prox = *lista_de_vertices;
}

void calcular_nova_aresta(int *aresta_atual, int *aresta_min,int *aresta_max,int *tem_caminho,int *acabou){
    int aux;
    if(*tem_caminho == 1){
        aux = *aresta_atual;
        *aresta_atual = (*aresta_min + *aresta_atual)/2;
        *aresta_max = aux;
        if (aux == *aresta_atual){
            *acabou = 1;
        }
    }else{
        aux = *aresta_atual;
        *aresta_atual = (*aresta_max + *aresta_atual)/2;
        *aresta_min = aux;  
        if (aux == *aresta_atual){
            *acabou = 2;
        }
    }
    *tem_caminho = 0;
}

int chega_em_um_lugia(p_grafo g,int quantidade_de_lugias,int distancia_maxima,int v){
    for(int i = 0;i<quantidade_de_lugias;i++){
        if(g->matriz_distancias[i][v]<= distancia_maxima){
            return 1;
        }
    }
    return 0;
}

int busca_rec(p_grafo g, int *visitado , int v,int quantidade_de_lugias,int distancia_maxima) {
    int w;
    if (chega_em_um_lugia(g,quantidade_de_lugias,distancia_maxima,v)){
        return 1;
        }
    visitado[v] = 1;
    for (w = quantidade_de_lugias; w < g->n; w++){
        if (g->matriz_distancias[v][w]<= distancia_maxima && !visitado[w]){
            if (busca_rec(g, visitado , w,quantidade_de_lugias, distancia_maxima)){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int quantidade_de_vertices = 0,quantidade_de_lugias = 0;
    p_vertice lista_de_vertices = NULL,lista_de_lugias = NULL;
    Vertice inicio;

    receber_ponto_inicial(&inicio);
    receber_entrada(&lista_de_vertices,&lista_de_lugias,&quantidade_de_vertices,&quantidade_de_lugias);

    Grafo grafo = inicializar_grafo();
    int aresta_min = 2147483647,aresta_max = 0,aresta_atual;

    armazenar_vertices_no_grafo(&grafo,lista_de_lugias,quantidade_de_vertices);
    criar_matriz_de_distancias(&grafo,&aresta_min,&aresta_max,&aresta_atual);
    int *ja_foram = malloc(grafo.n * sizeof(int));
    int acabou = 0,tem_caminho = 0;

    while(acabou == 0){
        zerar_vetor(ja_foram,quantidade_de_vertices);
        for(int i = 0;i<quantidade_de_lugias;i++){ // CONFERE SE EXISTE CAMINHO DIRETO DA ORIGEM ATE UM LUGIA
            if(distancia_inteira(grafo.vertices[i],&inicio)<=aresta_atual){
                tem_caminho = 1;
            }
        }
        for(int i = quantidade_de_lugias;i<quantidade_de_vertices && tem_caminho == 0;i++){
            if(distancia_inteira(&inicio,grafo.vertices[i])<=aresta_atual && tem_caminho == 0){
                tem_caminho = busca_rec(&grafo, ja_foram , i,quantidade_de_lugias,aresta_atual);
            }
        }
        calcular_nova_aresta(&aresta_atual,&aresta_min,&aresta_max,&tem_caminho,&acabou);

    }
    liberar_grafo(&grafo);
    free(ja_foram);
    if (acabou == 1){
        printf("%d",aresta_atual);
    }else{
        printf("%d",aresta_max);
    }
}