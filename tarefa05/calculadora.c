#include <stdio.h>
#include <stdlib.h>
#define MAX 25;

typedef struct No{
    int numero;
    struct No *prox;
} No;

typedef struct No * p_no;

p_no criar_lista(){
    return NULL;
}

p_no adicionar_na_lista(No *lista,char digito){
    p_no novo;
    novo = malloc(sizeof(No));
    novo->prox=lista;
    novo->numero = (int)digito;
    return novo;
}

void chamar_operacao(char operacao,No *num1,No *num2){
    if (operacao == '+'){
        somar(num1,num2);
    }else if(operacao == '-'){
        subtrair(num1,num2);
    }else if(operacao == '*'){
        multiplicar(num1,num2);
    }else{
        dividir(num1,num2);
    }
}

void armazenar_numero(p_no num1){
    char digito;
    for(int j = 0;j<MAX;j++){
        scanf("%c",&digito);
        if (digito == ' '){
            break;
        }
        num1 = adicionar_na_lista(num1,digito);
    }
}


int main(){
    int n;
    scanf("%d",&n);
    for (int i = 0;i<n;i++){

        char operacao;
        scanf("%c",&operacao);

        p_no num1= criar_lista(),p_no num2= criar_lista();
        armazenar_numero(num1);
        armazenar_numero(num2);

        chamar_operacao(operacao,num1,num2)

    }
}