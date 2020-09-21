#include <stdio.h>

int contar_acertos(int i,int nums_sorteados[6],int apostas[][60]){
    int j;
    int contador = 0;
    for(j = 0;j<6;j++){
        if (apostas[i][nums_sorteados[j]-1] == 1){
            contador ++;
        }
    }
    return contador;
}

void anunciar_premiados(double premio,int pedacos_do_premio[6],int quant_acertos[1000],int quant_de_apostas_por_acerto[6],int quant_apostas){
    int i;
    for (i = 0; i <quant_apostas;i++){
        printf("%.2lf\n",premio*pedacos_do_premio[quant_acertos[i]-1]/100/quant_de_apostas_por_acerto[quant_acertos[i]-1]);
    }
}


int main(){
    int quant_apostas,apostas[1000][60],nums_sorteados[6],quant_acertos[1000];
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
        quant_acertos[i] = contar_acertos(i,nums_sorteados,apostas);
    }

    int quant_de_apostas_por_acerto[6];

    for (i = 0; i <quant_apostas;i++){
        quant_de_apostas_por_acerto[quant_acertos[i]-1]++;
    }
    int pedacos_do_premio[6] = {0,0,0,19,19,62};

    anunciar_premiados(premio,pedacos_do_premio,quant_acertos,quant_de_apostas_por_acerto,quant_apostas);
        
}