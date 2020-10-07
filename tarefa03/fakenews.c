﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct noticia{
    char *nome;
    int tipo;
    double media,desvio,menor,maior;
} Noticia;

void receber_noticia(int M,Noticia *noticia){
    int j;
    double valor_atual,media_atual,desvio_atual;
    double *valores_atuais;

    noticia->nome = malloc(25*sizeof(char));
    scanf("%s",noticia->nome);

    valores_atuais = malloc(M*sizeof(double));
    desvio_atual = 0;
    media_atual = 0;

    for (j = 0;j<M;j++){
        scanf(" %lf",valores_atuais+j);
    }

    double menor = *valores_atuais,maior = *valores_atuais;

    for (j = 0;j<M;j++){
        valor_atual = valores_atuais[j];
        media_atual += valor_atual;
        if (valor_atual < menor){
            menor = valor_atual;
        }
        if (valor_atual > maior){
            maior = valor_atual;
        }
    }

    media_atual = media_atual/M;
    for (j = 0;j<M;j++){
        desvio_atual += (valores_atuais[j]-media_atual)*(valores_atuais[j]-media_atual);
    }
    free(valores_atuais);
    desvio_atual = sqrt( desvio_atual/(M) );
    noticia->media = media_atual;
    noticia->desvio = desvio_atual;
    noticia->menor = menor;
    noticia->maior = maior;
}

void escrever_noticia(Noticia *noticia){
    printf("%s %.2lf %.2lf %.2lf %.2lf\n",noticia->nome,noticia->maior,noticia->menor,noticia->media,noticia->desvio);
}

void string(char *inicio,char str[]){
    int i;
    for(i=0;str[i]!='\0';i++){
        *(inicio+i) = str[i];
    }
    *(inicio+i)= '\0';
}

void relatorio(int N,Noticia *noticias){
    int i,j,qt_tipos_de_noticia = 5, quantidades_de_noticias[5] = {0,0,0,0,0};
    char **tipos_de_noticias;



    tipos_de_noticias = malloc(qt_tipos_de_noticia*sizeof(char*));

    for (i=0;i<qt_tipos_de_noticia;i++){
        *(tipos_de_noticias+i) = malloc(20*sizeof(char));
    }

    string(*(tipos_de_noticias + 0),"Bot");
    string(*(tipos_de_noticias + 1),"Surpreendente");
    string(*(tipos_de_noticias + 2),"Normal");
    string(*(tipos_de_noticias + 3),"Local");
    string(*(tipos_de_noticias + 4),"Irrelevante");

    for (i=0;i<N;i++){
        if ((noticias+i)->media >= 60 ){
            if ((noticias+i)->desvio >15){
                quantidades_de_noticias[0] ++;
                (noticias+i)->tipo = 0;
            }else{
                quantidades_de_noticias[1]++;
                (noticias+i)->tipo = 1;
            }
        }else{
            if((noticias+i)->maior >=80){
                if((noticias+i)->menor >20){
                    quantidades_de_noticias[2]++;
                    (noticias+i)->tipo = 2;
                }else{
                    quantidades_de_noticias[3]++;
                    (noticias+i)->tipo = 3;

                }
            }else{
                quantidades_de_noticias[4]++;
                (noticias+i)->tipo = 4;
            }
        }
    }
    printf("\n");
    printf("RESULTADO:\n");
    for (i = 0; i< qt_tipos_de_noticia;i++){
        printf("%s (%d): ",*(tipos_de_noticias+i),quantidades_de_noticias[i]);
        for(j=0;j<N;j++){
            if((noticias+j)->tipo == i){
                printf("%s ",(noticias+j)->nome);
            }
        }
        printf("\n");
    }

    free(tipos_de_noticias);
}

int main(){
    Noticia *noticias;
    int i,N,M;

    scanf("%d %d",&N,&M);
    noticias = malloc(N*sizeof(Noticia));

    for (i = 0; i<N;i++){
        receber_noticia(M,noticias+i);
    }

    for (i = 0; i<N;i++){
        escrever_noticia(noticias+i);
    }
    relatorio(N,noticias);

    for (i = 0; i<N;i++){
        free((noticias+i)->nome);
    }
    free(noticias);
}

