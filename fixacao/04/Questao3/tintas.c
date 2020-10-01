#include "tintas.h"

Tinta inicializar_tinta(double amarelo,double vermelho,double azul){
    Tinta tinta;
    /*Quando tem 0 em todas as cores a tinta é preta
      Quanto tem todas iguais diferentes de 0 é branca
      Fora isso é colorida*/

    if (amarelo == vermelho && vermelho == azul){
        if (amarelo == 0){
            tinta.colorida_branca_ou_preta = 2;
            return tinta;
        }
        tinta.colorida_branca_ou_preta = 1;
        return tinta;
        }

    tinta.colorida_branca_ou_preta = 0;

    double total = amarelo+vermelho+azul;
    tinta.pctg_amrl = amarelo/total;
    tinta.pctg_verm = vermelho/total;
    tinta.pctg_azul = azul/total;
    return tinta;
}

Tinta misturar_tintas(Tinta tinta1,Tinta tinta2,double pctg1,double pctg2){
    Tinta resultado;
    if (tinta1.colorida_branca_ou_preta == 2 || tinta2.colorida_branca_ou_preta == 2){
        resultado.colorida_branca_ou_preta = 2;
        return resultado;
    }
    if (tinta1.colorida_branca_ou_preta == 1 && tinta2.colorida_branca_ou_preta == 1){
        resultado.colorida_branca_ou_preta =1;
        return resultado;
    }
    resultado.colorida_branca_ou_preta = 0;

    if (tinta1.colorida_branca_ou_preta == 1){
        resultado.pctg_amrl = tinta2.pctg_amrl;
        resultado.pctg_verm = tinta2.pctg_verm;
        resultado.pctg_azul = tinta2.pctg_azul;
    } else if (tinta2.colorida_branca_ou_preta == 1){
        resultado.pctg_amrl = tinta1.pctg_amrl;
        resultado.pctg_verm = tinta1.pctg_verm;
        resultado.pctg_azul = tinta1.pctg_azul;
    } else{
        resultado.pctg_amrl = (pctg1*tinta1.pctg_amrl+pctg2*tinta2.pctg_amrl);
        resultado.pctg_verm = (pctg1*tinta1.pctg_verm+pctg2*tinta2.pctg_verm);
        resultado.pctg_azul = (pctg1*tinta1.pctg_azul+pctg2*tinta2.pctg_azul);     
    }
    return resultado;
}