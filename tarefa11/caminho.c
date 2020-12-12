#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Vertice {
    double x,y;
    int eh_lugia;
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

p_vertice adicionar_vertice(p_vertice lista,double x, double y,int eh_lugia){

    p_vertice novo = malloc(sizeof(Vertice));
    novo->x = x;
    novo->y = y;
    novo->eh_lugia = eh_lugia;
    novo->prox =  lista;

    return novo;
}

int distancia_inteira(p_vertice no1,p_vertice no2){
    double distancia = 0;
    distancia += (no1->x-no2->x)*(no1->x-no2->x);
    distancia += (no1->y-no2->y)*(no1->y-no2->y);
    distancia = sqrt(distancia);
    int resultado = (int)distancia;
    return resultado+1;
}

void armazenar_vertices_no_grafo(p_grafo grafo, p_vertice lista_de_vertices){
    grafo->vertices = malloc(sizeof(p_vertice)*grafo->n);
    for(int i = 0;i<grafo->n;i++){
        grafo->vertices[i] = lista_de_vertices;
        lista_de_vertices = lista_de_vertices->prox;
    }
}

void criar_matriz_de_distancias(p_grafo grafo,int *aresta_min,int *aresta_max){
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
}

int ja_foi(int valor,int *ja_foram,int aux){
    for (int i = 0;i<aux;i++){
        if(ja_foram[i] == valor){
            return 1;
        }
    }
    return 0;
}

void calcular_nova_aresta(int *aresta_atual, int *aresta_min,int *aresta_max,int tem_caminho,int *acabou){
    int aux;
    if(tem_caminho == 1){
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
}

void testar_se_tem_caminho(Grafo grafo,int *ja_foram,int *aux,int atual,int distancia_max,int *tem_caminho){
    int tamanho_aresta;

    if(grafo.vertices[atual]->eh_lugia == 1){
        *tem_caminho = 1;
    }else{
        *aux += 1;
        for(int i = 0;i<grafo.n && *tem_caminho == 0;i++){
            tamanho_aresta = grafo.matriz_distancias[i][atual];
            if(tamanho_aresta <= distancia_max && ja_foi(i,ja_foram,*aux )==0 && *tem_caminho == 0 ){
                ja_foram[*aux-1] = i;
                testar_se_tem_caminho(grafo, ja_foram,aux,i,distancia_max,tem_caminho);
            }
        }
        *aux -= 1;

    }
}

int main(){
    int quantidade_de_vertices = 0;
    char tipo[15];
    double x_atual,y_atual;
    double x_inicial,y_inicial;
    p_vertice lista_de_vertices = NULL;

    Vertice inicio;
    scanf(" %lf %lf", &x_inicial,&y_inicial);
    inicio.x = x_inicial;
    inicio.y = y_inicial;
    inicio.eh_lugia = 0;
    inicio.prox = NULL;

    while (scanf(" %lf %lf %s",&x_atual,&y_atual,tipo) > 0){
        quantidade_de_vertices += 1;
        if (tipo[0] == 'L'){
            lista_de_vertices = adicionar_vertice(lista_de_vertices,x_atual,y_atual,1);
        }else{
            lista_de_vertices = adicionar_vertice(lista_de_vertices,x_atual,y_atual,0);
        }
    }
    Grafo grafo = inicializar_grafo();

    grafo.n = quantidade_de_vertices;
    armazenar_vertices_no_grafo(&grafo,lista_de_vertices);
    int aresta_min = 2147483647,aresta_max = 0,aresta_atual;
    criar_matriz_de_distancias(&grafo,&aresta_min,&aresta_max);

    int *ja_foram = malloc((grafo.n+1)*sizeof(int));
    int aux = 0; // quantos numeros temos em ja_foram
    int tem_caminho = 0;
    int acabou = 0;
    aresta_atual = (aresta_max + aresta_min)/2;
    //printf("%d %d %d\n",aresta_max, aresta_atual,aresta_min);
    for(int i = 0;i<quantidade_de_vertices && tem_caminho == 0;i++){
        ja_foram[aux] = i;
        aux += 1;
        if(distancia_inteira(&inicio,grafo.vertices[i])<=aresta_atual){
            testar_se_tem_caminho(grafo, ja_foram,&aux,i,aresta_atual,&tem_caminho);
        }
        aux -= 1;
    }
    calcular_nova_aresta(&aresta_atual,&aresta_min,&aresta_max,tem_caminho,&acabou);
    //printf("%d %d %d\n",aresta_max, aresta_atual,aresta_min);
    while(acabou == 0){
        tem_caminho = 0;
        for(int i = 0;i<quantidade_de_vertices && tem_caminho == 0;i++){
            ja_foram[aux] = i;
            aux += 1;
            if(distancia_inteira(&inicio,grafo.vertices[i])<=aresta_atual && tem_caminho == 0){
                testar_se_tem_caminho(grafo, ja_foram,&aux,i,aresta_atual,&tem_caminho);
            }
            aux -= 1;
        }
        //printf("aresta: %d Tem caminho: %d\n",aresta_atual,tem_caminho);
        calcular_nova_aresta(&aresta_atual,&aresta_min,&aresta_max,tem_caminho,&acabou);
        //printf("%d %d %d\n",aresta_max, aresta_atual,aresta_min);
    }
    if (acabou == 1){
        printf("%d",aresta_atual);
    }else{
        printf("%d",aresta_max);
    }
}