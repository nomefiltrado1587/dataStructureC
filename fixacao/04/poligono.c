#include "poligono.h"

Ponto init_ponto(double cordx,double cordy){
    Ponto ponto;
    ponto.x = cordx;
    ponto.y = cordy;
    return ponto;
}

Poligono init_poligono(int n,Ponto vertices[100]){
    Poligono poligono;
    poligono.n_vertices = n;
    for (int i = 0;i<n;i++){
        poligono.vertices[i] = vertices[i];
    }
    return poligono;
}

double area_poligono(Poligono poligono){
    double area;
    int n = poligono.n_vertices;
    poligono.vertices[n] = poligono.vertices[0];
    for(int i = 0;i<n;i ++){
        area = area + poligono.vertices[i].x*poligono.vertices[i+1].y;
    }
    for(int i = 0;i<n;i++){
        area = area - poligono.vertices[i+1].x*poligono.vertices[i].y;
    }
    return area;
}

Poligono trasladar_poligono(Poligono poligono,double var_x,double var_y){
    for (int i =0;i<poligono.n_vertices;i++){
        poligono.vertices[i].x += var_x;
        poligono.vertices[i].y += var_y;
    }
    return poligono;
}