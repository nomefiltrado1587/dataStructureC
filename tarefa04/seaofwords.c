#include <stdio.h>
#include <stdlib.h>
#define MAX_PALAVRA 20

typedef struct matriz{
    int comprimento;
    int largura;
    char **elementos;
}Matriz;

typedef struct ponto{
    int i;
    int j;
}Ponto;

void receber_entrada(int *q, Matriz *matriz){
    scanf("%d %d %d",&matriz->comprimento,&matriz->largura,q);
    matriz->elementos = malloc(matriz->comprimento*sizeof(char*));

    for (int i = 0; i< matriz->comprimento;i++){
        matriz->elementos[i] = malloc(matriz->largura*sizeof(char));
    }
    for (int i = 0; i< matriz->comprimento;i++){
        scanf(" %s",matriz->elementos[i]);
    }
}

int verificar_pontos(int i, int j,int letra_atual,Ponto posicoes_ja_utilizadas[MAX_PALAVRA]){
    // VERIFICA SE O PONTO (i,j) JA FOI UTILIZADO NA BUSCA ATUAL

    for(int k =  0;k<letra_atual;k++){
        if (i == posicoes_ja_utilizadas[k].i && j == posicoes_ja_utilizadas[k].j){
            return 1;
        }
    }
    return 0;
}

void verificar_posicao(int i,int j,int letra_atual,char palavra_atual[MAX_PALAVRA],Matriz matriz,Ponto posicoes_ja_utilizadas[MAX_PALAVRA],int *verificar_se_acabou){
    // VE SE A POSIÇÃO i,j DA MATRIZ CONTEM A LETRA ATUAL DA PALAVRA BUSCADA
    // CASO CONTENHA, SAO PESQUISADOS AS 4 POSIÇOES ADJACENTES (CASO NAO TENHAM SIDO PESQUISADAS E ESTEJAM CONTIDAS NA MATRIZ)

    if (*verificar_se_acabou == 0 && matriz.elementos[i][j] == palavra_atual[letra_atual]){
        if (palavra_atual[letra_atual+1] == '\0'){
            *verificar_se_acabou = 1;
            return;
        }

        posicoes_ja_utilizadas[letra_atual].i = i;
        posicoes_ja_utilizadas[letra_atual].j = j;
        if (i != 0 && verificar_pontos(i-1,j,letra_atual,posicoes_ja_utilizadas)==0){
            verificar_posicao(i-1,j,letra_atual+1,palavra_atual,matriz,posicoes_ja_utilizadas,verificar_se_acabou);
        }
        if (i != matriz.comprimento-1 && verificar_pontos(i+1,j,letra_atual,posicoes_ja_utilizadas)==0){
            verificar_posicao(i+1,j,letra_atual+1,palavra_atual,matriz,posicoes_ja_utilizadas,verificar_se_acabou);
        }
        if (j != 0 && verificar_pontos(i,j-1,letra_atual,posicoes_ja_utilizadas)==0){
            verificar_posicao(i,j-1,letra_atual+1,palavra_atual,matriz,posicoes_ja_utilizadas,verificar_se_acabou);
        }
        if (j != matriz.largura-1 && verificar_pontos(i,j+1,letra_atual,posicoes_ja_utilizadas)==0){
            verificar_posicao(i,j+1,letra_atual+1,palavra_atual,matriz,posicoes_ja_utilizadas,verificar_se_acabou);
        }
    }


}


void procurar_palavra(Matriz matriz,char palavra_atual[MAX_PALAVRA]){
    //VERIFICA SE UMA PALAVRA ESTA CONTIDA NA MATRIZ
    int verificar_se_acabou = 0;
    for(int j = 0;j<matriz.comprimento;j++){
        for(int k = 0;k<matriz.largura;k++){
            Ponto posicoes_ja_utilizadas[MAX_PALAVRA];
            int letra_atual = 0;
            verificar_posicao(j,k,letra_atual,palavra_atual,matriz,posicoes_ja_utilizadas,&verificar_se_acabou);
            if (verificar_se_acabou == 1){
                break;
            }
        }
        if (verificar_se_acabou == 1){
            break;
        }
    }
    if (verificar_se_acabou == 1){
        printf("sim\n");
    }else{
        printf("nao\n");
    }
}


void liberar_matriz(Matriz *matriz){
    for (int i = 0; i<matriz->comprimento;i++){
        free(matriz->elementos[i]);
    }
    free(matriz->elementos);
}

int main(){
    Matriz matriz;
    int q;

    receber_entrada(&q,&matriz);

    for(int i = 0; i< q; i++){
        char palavra_atual[MAX_PALAVRA];
        scanf(" %s",palavra_atual);
        procurar_palavra(matriz,palavra_atual);
    }

    liberar_matriz(&matriz);
}