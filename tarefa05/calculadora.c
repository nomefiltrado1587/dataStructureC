#include <stdio.h>
#include <stdlib.h>
#define MAX 25

typedef struct No{
    int dado;
    struct No *prox;
    struct No *ant;
} No;

typedef struct No * p_no;

typedef struct Numero_grande{
    int comprimento;
    p_no digitos;
} Numero_grande;

p_no adicionar_elemento(p_no lista,int dado){
    p_no novo;
    novo = malloc(sizeof(No));
    novo->dado = dado;
    if (lista == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        lista = novo;
    } else {

        novo->ant = lista;
        lista->prox->ant = novo;
        novo->prox = lista->prox;
        lista->prox = novo;
    }
    return lista;
}

p_no remover_da_lista(p_no no){
    p_no ant = no->ant;
    (no->prox)->ant = no->ant;
    (no->ant)->prox = no->prox;
    free(no);
    return ant;
}

void imprimir_lista(p_no lista) {
    p_no inicial = lista;
    do{
        printf("%d",lista->dado);
        lista = lista->ant;
    }while(lista != inicial);
    printf("\n");
}

void armazenar_numero(char *numero,Numero_grande *num){
    int dado;
    for(int i = 0;numero[i] != '\0';i++){
        num->comprimento +=1;
        dado = numero[i]-48;
        num->digitos = adicionar_elemento(num->digitos,dado);
    }
}

void receber_numero(Numero_grande *num){
    char numero[25];
    num->digitos = NULL;
    num->comprimento = 0;
    scanf(" %s",numero);
    armazenar_numero(numero,num);
}


void realizar_operacao(){
    char tipo_operacao;
    Numero_grande num1,num2;
    scanf(" %c",&tipo_operacao);
    receber_numero(&num1);
    receber_numero(&num2);

    p_no resultado = NULL;
    if(tipo_operacao == '+'){
        imprimir_lista(resultado);
        resultado = somar(num1,num2);
        imprimir_lista(resultado);
    }
    if(tipo_operacao == '-'){
        p_no dale = num1.digitos->prox;
        int dado = dale->dado;
        printf("%d",dado);
        /*
        if(dado == 0){
            printf("0\n");
        }else{
            resultado =  subtrair(num1,num2);
            imprimir_lista(resultado);
        }
        */
    }
    /*
    if(tipo_operacao == '*'){
        multiplicar(num1,num2);
    }
    if(tipo_operacao == '/'){
        dividir(num1,num2);
    }
    */
    destruir_lista(num1.digitos);
    destruir_lista(num2.digitos);
    destruir_lista(resultado);

}


int main(){
    int n;
    scanf("%d",&n);

    for (int i = 0;i<n;i++){
        realizar_operacao();
    }
}