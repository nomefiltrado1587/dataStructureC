#include <stdio.h>
#include <stdlib.h>
#define MAX 25;

typedef struct No{
    int digito;
    struct No *ant;
    struct No *prox;
} No;

typedef struct No * p_no;

typedef struct Numero_grande{
    int comprimento;
    p_no digitos;
}

void printar_numero(Numero_grande numero){
    p_no digito_atual = (numero.digitos)->ant;
    for(int i = 0,i<numero.comprimento,i++){
        printf("%d",digito_atual->digito);
        digito_atual = digito_atual->ant;
    }
    printf("\n");
}

p_no criar_lista(){
    return NULL;
}

p_no adicionar_na_lista(p_no lista,char digito,p_no inicial){
    p_no novo;
    novo = malloc(sizeof(No));
    if (lista == NULL){
        novo->prox = novo;
        novo->ant = novo;
        lista = novo;
    }else{
        novo->prox= lista->prox;
        novo->ant = lista;
        lista->prox = novo;
        novo->digito = (int)digito;
    }
    return lista;
}

void somar(Numero_grande num1,Numero_grande num2){
    p_no resultado;
    p_no inicial1 = num1.digitos,inicial2 = num2.digitos;
    p_no digito_atual1 = inicial1,digito_atual2 = inicial2
    
    
    int soma_atual = 0;
    int acabou1= 0, acabou2= 0;

    while(acabou1 == 0 && acabou2 == 0){
        if(acabou1 == 0){
            soma_atual += digito_atual1->digito;
            digito_atual1 = digito_atual1->prox;
            if (digito_atual1 == inicial1){
                acabou1 =1;
            }
        }
        if(acabou2 == 0){
            soma_atual += digito_atual2->digito;
            digito_atual2 = digito_atual2->prox;
            if (digito_atual2 == inicial2){
                acabou2 =1;
            }
        }
        adicionar_na_lista(resultado,soma_atual);
        soma_atual = soma_atual/10;
    }
}


void subtrair(Numero_grande num1,Numero_grande num2){
    if (num1.comprimento < num2.comprimento){
        subtrair(num2,num1);
        return;
    }
    if (num1.comprimento == num2.comprimento && num1->digitos->digito < num2->digitos->digito){
        subtrair(num2,num1);
        return;
    }
    p_no resultado = criar_lista();
    p_no inicial1 = num1.digitos,inicial2 = num2.digitos;
    p_no digito_atual1 = num1.digitos,digito_atual2 = num2.digitos;

    int subtracao_atual = 0;
    int acabou1= 0, acabou2= 0;
    while(acabou1 == 0 && acabou2 == 0){

        subtracao_atual += digito_atual1->digito;
        digito_atual1 = digito_atual1->prox;
        if (digito_atual1 == inicial1){
            acabou1 =1;
        }
        
        if(acabou2 == 0){
            if(digito_atual2->digito > subtracao_atual){
                subtracao_atual += 10;
                digito_atual1->digito -= 1; 
            }
            subtracao_atual -= digito_atual2->digito;
            digito_atual2 = digito_atual2->prox;
            if (digito_atual2 == inicial2){
                acabou2 =1;
            }
        }
        adicionar_na_lista(resultado,subtracao_atual);
    }
    printf("\n");
}


}

void chamar_operacao(char operacao,Numero_grande num1,Numero_grande num2){
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
    inicial = num1;

    for(int j = 0;j<MAX;j++){
        scanf("%c",&digito);
        if (digito == ' '){
            break;
        }
        num1 = adicionar_na_lista(num1,digito,inicial);
    }


}


int main(){
    int n;
    scanf("%d",&n);
    for (int i = 0;i<n;i++){

        char operacao;
        scanf("%c",&operacao);

        NUMERO num1 , num2;
        num1.digitos = criar_lista();
        num2.digitos = criar_lista();

        armazenar_numero(num1.digitos);
        armazenar_numero(num2.digitos);

        chamar_operacao(operacao,num1,num2);

    }
}