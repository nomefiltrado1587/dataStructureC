#include <stdio.h>

int potencia(int n,int contador, double a,double valor){
    if (contador == n){
        return valor;
    }
    return valor*a;
}

int main(){
    int n = 5;
    double a = 2;
    printf("%lf",potencia(n,0,a,1));
}