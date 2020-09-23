#include <stdio.h>

void receber_entrada(int quant_apostas,int apostas[][60],int nums_sorteados[]){
    int i,j;
    for (i = 0;i<quant_apostas;i++)
        for(j = 0;j<60;j++)
            scanf(" %d",&apostas[i][j]);

    for (i = 0;i<6;i++)
        scanf("%d",&nums_sorteados[i]);
}

void contar_acertos(int quant_acertos[1000],int nums_sorteados[6],int apostas[][60],int quant_apostas){
    // CONTA QUANTOS ACERTOS CADA JOGADOR FEZ E OS ARMAZENA EM "quant_acertos"
    int i,j;
    int contador;
    for (i = 0;i<quant_apostas;i++){
        contador = 0;
        for(j = 0;j<6;j++)
            if (apostas[i][nums_sorteados[j]-1] == 1){
                contador ++;
            }
        quant_acertos[i] = contador;
    }
}

int main(){
    int quant_apostas,apostas[1000][60],nums_sorteados[6],quant_acertos[1000];
    double premio;

    scanf(" %d %lf",&quant_apostas,&premio);

    receber_entrada(quant_apostas,apostas,nums_sorteados);

    contar_acertos(quant_acertos,nums_sorteados,apostas,quant_apostas);

    int quant_de_apostas_por_acertos[7]={0,0,0,0,0,0,0}; 
    /*  é a quantidade de apostas que tiveram determinada quantidade de acertos
    exmp: quant_de_apostas_por_acerto[3] == 5 <-> 5 apostas tiveram exatamente 3 acertos      */
    int i;
    for (i = 0; i <quant_apostas;i++)
        quant_de_apostas_por_acertos[quant_acertos[i]]++;

    double porcentagens_do_premio[7] = {0,0,0,0,0.19,0.19,0.62};
    double premio_atual; // a bolada que cada um irá ganhar
    for (i = 0; i <quant_apostas;i++){
        premio_atual = premio*porcentagens_do_premio[quant_acertos[i]]/quant_de_apostas_por_acertos[quant_acertos[i]];
        printf("%.2lf\n",premio_atual);
    }
}