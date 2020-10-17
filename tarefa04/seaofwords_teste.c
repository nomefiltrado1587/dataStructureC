#include <stdio.h>
#include <stdlib.h>

#define MAX_PALAVRA 20

typedef struct matriz{
    char **elementos;
    int comprimento;
    int largura;
}Matriz;

int ver_se_ja_utilizamos(int i, int j,int letra_atual, int posicoes_ja_utilizadas[][2]){
    for (int k = 0;k<letra_atual;k++){
        if (i == posicoes_ja_utilizadas[k][0] && j == posicoes_ja_utilizadas[k][1]){
            return 1;
        }
    }
    return 0;
}

void conferir(int *boolean,char *palavra_atual,Matriz matriz,int letra_atual,int i,int j,int posicoes_ja_utilizadas[][2]){

    if (matriz.elementos[i][j] == palavra_atual[letra_atual] && *boolean == 0){

        if (palavra_atual[letra_atual+1] == '\0'){
            *boolean = 1;
            return;
        }

        posicoes_ja_utilizadas[letra_atual][0] = i;
        posicoes_ja_utilizadas[letra_atual][1] = j;

        if (i !=0 && ver_se_ja_utilizamos(i-1,j,letra_atual,posicoes_ja_utilizadas) == 0){
            conferir(boolean,palavra_atual,matriz,letra_atual+1,i-1,j,posicoes_ja_utilizadas);
        }
        if (i != matriz.largura-1 && ver_se_ja_utilizamos(i+1,j,letra_atual+1,posicoes_ja_utilizadas)==0 ){
            conferir(boolean,palavra_atual,matriz,letra_atual+1,i+1,j,posicoes_ja_utilizadas);
        }
        if (j !=0 && ver_se_ja_utilizamos(i,j-1,letra_atual+1,posicoes_ja_utilizadas)==0){
            conferir(boolean,palavra_atual,matriz,letra_atual+1,i,j-1,posicoes_ja_utilizadas);
        }
        if (j != matriz.largura-1 && ver_se_ja_utilizamos(i,j+1,letra_atual,posicoes_ja_utilizadas)==0){
            conferir(boolean,palavra_atual,matriz,letra_atual+1,i,j+1,posicoes_ja_utilizadas);
        }
    }

}

int main(){
    int q;
    int i,j,k,posicoes_ja_utilizadas[MAX_PALAVRA][2];
    char palavra_atual[MAX_PALAVRA];
    int *boolean;
    Matriz matriz;

    scanf("%d %d %d",&matriz.comprimento,&matriz.largura,&q);

    matriz.elementos = malloc(matriz.comprimento*sizeof(char*));
    for (i = 0; i<matriz.comprimento;i++){
        matriz.elementos[i] = malloc(matriz.largura*sizeof(char));
        scanf(" %s",matriz.elementos[i]);
    }

    boolean = malloc(sizeof(int));
    for(i = 0;i<q;i++){
        scanf(" %s",palavra_atual);
        *boolean = 0;
        for(j = 0;j<matriz.comprimento;j++){
            for(k = 0;k<matriz.largura;k++){
                int letra_atual = 0;
                conferir(boolean,palavra_atual,matriz,letra_atual,j,k,posicoes_ja_utilizadas);
                }
            }
        if (*boolean == 0){
        printf("nao\n");
        } else{
            printf("sim\n");
        }
    }

    for (i = 0; i<matriz.comprimento;i++){
        free(matriz.elementos[i]);
    }
    free(matriz.elementos);
}