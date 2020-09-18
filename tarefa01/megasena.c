#include <stdio.h>


int main(){
    int quant_apostas,apostas[1000][60],nums_sorteados[6],quant_acertos[1000],contador;
    int i,j;
    double premio;

    scanf(" %d %lf",&quant_apostas,&premio);
    for (i = 0;i<quant_apostas;i++){
        for(j = 0;j<60;j++){
            scanf(" %d",&apostas[i][j]);
        }
    }
    for (i = 0;i<6;i++){
        scanf("%d",&nums_sorteados[i]);
    }


    for (i = 0;i<quant_apostas;i++){
        contador = 0;
        for(j = 0;j<6;j++){
            if (apostas[i][nums_sorteados[j]-1] == 1){
                contador ++;
            }
        }
        quant_acertos[i] = contador;
    }

    int quant_de_apostas_por_acerto[6];



    for (i = 0; i <quant_apostas;i++){
        quant_de_apostas_por_acerto[quant_acertos[i]-1]++;
    }
    int divisoes_do_premio[6] = {0,0,0,19,19,62};


    for (i = 0; i <quant_apostas;i++){
            /*printf("%d %d %d\n",divisoes_do_premio[quant_acertos[i]-1],quant_de_apostas_por_acerto[quant_acertos[i]-1],quant_acertos[i]-1); */
            printf("%.2lf\n",premio*divisoes_do_premio[quant_acertos[i]-1]/100/quant_de_apostas_por_acerto[quant_acertos[i]-1]);
    }

}