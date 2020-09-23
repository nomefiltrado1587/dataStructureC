#include <stdio.h>

void receber_entrada(int quant_apostas,int apostas[][60],int nums_sorteados[]){
    int i,j;
    for (i = 0;i<quant_apostas;i++)
        for(j = 0;j<60;j++)
            scanf(" %d",&apostas[i][j]);

    for (i = 0;i<6;i++)
        scanf("%d",&nums_sorteados[i]);
}

int contar_acertos(int i,int nums_sorteados[6],int apostas[][60]){
    int j;
    int contador = 0;
    for(j = 0;j<6;j++)
        if (apostas[i][nums_sorteados[j]-1] == 1){
            contador ++;
        }
    return contador;
}

void anunciar_premiados(double premio,int pedacos_do_premio[6],int quant_acertos[1000],int quant_de_apostas_por_acertos[6],int quant_apostas){
    int i,pedaco_do_premio;
    for (i = 0; i <quant_apostas;i++){
        pedaco_do_premio = pedacos_do_premio[quant_acertos[i]];
        printf("%.2lf\n",premio*pedaco_do_premio/100/quant_de_apostas_por_acertos[quant_acertos[i]]);
    }
}


int main(){
    int quant_apostas=0,apostas[1000][60],nums_sorteados[6],quant_acertos[1000];
    int i;
    double premio=0;

    scanf(" %d %lf",&quant_apostas,&premio);
    receber_entrada(quant_apostas,apostas,nums_sorteados);

    for (i = 0;i<quant_apostas;i++)
        quant_acertos[i] = contar_acertos(i,nums_sorteados,apostas);

    int quant_de_apostas_por_acertos[7];

    for (i = 0; i <quant_apostas;i++)
        quant_de_apostas_por_acertos[quant_acertos[i]]++;

    int pedacos_do_premio[7] = {0,0,0,0,19,19,62};

    anunciar_premiados(premio,pedacos_do_premio,quant_acertos,quant_de_apostas_por_acertos,quant_apostas);
        
}