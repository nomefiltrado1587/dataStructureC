#include "tintas.h"
#include <stdio.h>
int main(){
    double vermelho[2],amarelo[2],azul[2];
    Tinta tinta1, tinta2,tinta3;

    for (int i = 0; i<2 ;i++){
    printf("Digite um valor para vermelho: ");
    scanf(" %lf",(vermelho+i));
    printf("\nDigite um valor para amarelo: ");
    scanf(" %lf",(amarelo+i));
    printf("\nDigite um valor para azul: ");
    scanf(" %lf",(azul+i));
    }
    tinta1 = inicializar_tinta(amarelo[0],vermelho[0],azul[0]);
    tinta2 = inicializar_tinta(amarelo[1],vermelho[1],azul[1]);

    tinta3 = misturar_tintas(tinta1,tinta2,0.56,0.44);

    printf("%lf",tinta3.pctg_verm);


    return 0;
}