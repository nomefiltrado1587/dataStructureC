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

void armazenar_numero(char *numero,Numero_grande *num){
    int dado;
    for(int i = 0;numero[i] != '\0';i++){
        num->comprimento +=1;
        dado = numero[i]-48;
        num->digitos = adicionar_elemento(num->digitos,dado);
    }
}

void destruir_lista(p_no lista){
    p_no inicial = lista;
    p_no prox;
    while(lista->prox != inicial){
        prox = lista->prox;
        free(lista);
        lista = prox;
    }
    free(lista);
}

void imprimir_lista(p_no lista) {
    p_no inicial = lista;
    do{
        printf("%d",lista->dado);
        lista = lista->ant;
    }while(lista != inicial);
    printf("\n");
}

void imprimir_lista_invertida(p_no lista) {
    p_no inicial = lista;
    do{
        lista = lista->prox;
        printf("%d",lista->dado);
    }while(lista != inicial);
    printf("\n");
}

p_no remover_da_lista(p_no no){
    p_no prox = no->prox;
    (no->prox)->ant = no->ant;
    (no->ant)->prox = no->prox;
    free(no);
    return prox;
}

void receber_numero(Numero_grande *num){
    char numero[25];
    num->digitos = NULL;
    num->comprimento = 0;
    scanf(" %s",numero);
    armazenar_numero(numero,num);
}

p_no somar(Numero_grande num1,Numero_grande num2){
    if(num1.comprimento < num2.comprimento){
        return somar(num2,num1);
    }
    p_no resultado = NULL,inicial1 = num1.digitos->prox,inicial2 = num2.digitos->prox;
    p_no digito_atual1 = num1.digitos->prox,digito_atual2 = num2.digitos->prox;
    int soma_atual;
    int acabou1=0,acabou2 = 0;
    resultado = adicionar_elemento(resultado,0);
    while(acabou1 == 0){
        soma_atual = 0;
        resultado = adicionar_elemento(resultado,0);

        soma_atual  += digito_atual1->dado;
        if(digito_atual1->prox == inicial1){
            acabou1 = 1;
        }else{
            digito_atual1 = digito_atual1->prox;
        }
        if (acabou2 == 0){
            soma_atual  += digito_atual2->dado;
            if(digito_atual2->prox == inicial2){
                acabou2 = 1;
            }else{
                digito_atual2 = digito_atual2->prox;
            }
        }
        resultado->prox->dado = (soma_atual+resultado->dado)%10;
        resultado->dado = (soma_atual+resultado->dado)/10;
    }
    if(resultado->dado == 0){
        resultado = remover_da_lista(resultado);
    }
    return resultado->ant;
}

p_no subtrair(Numero_grande num1,Numero_grande num2){
    if(num1.comprimento < num2.comprimento){
        return subtrair(num2,num1);
    }
    if(num1.comprimento == num2.comprimento){
        p_no digito1= num1.digitos,digito2= num2.digitos;
        for(int i =0;i<num1.comprimento;i++){
            if(digito1->dado < digito2->dado){
                return subtrair(num2,num1);
            }
            digito1 = digito1->prox;
            digito2 = digito2->prox;
        }
    }

    p_no resultado = NULL,inicial1 = num1.digitos->prox,inicial2 = num2.digitos->prox;
    p_no digito_atual1 = num1.digitos->prox,digito_atual2 = num2.digitos->prox;
    int subtracao_atual=0;
    int acabou1=0,acabou2 = 0;

    while(acabou1 == 0){
        resultado = adicionar_elemento(resultado,0);
        resultado = resultado->prox;
        subtracao_atual += digito_atual1->dado;
        if (digito_atual1->prox == inicial1){
            acabou1 = 1;
        }else{
            digito_atual1 = digito_atual1->prox;
        }

        if (acabou2 == 0){
            if(digito_atual2->dado>subtracao_atual){
                resultado->dado = (subtracao_atual + 10 - digito_atual2->dado);
                subtracao_atual = -1;
            }else{
                resultado->dado = subtracao_atual - digito_atual2->dado;
                subtracao_atual = 0;
            }
            if (digito_atual2->prox == inicial2){
                acabou2 = 1;
            }else{
                digito_atual2 = digito_atual2->prox;
            }
        }else{
            resultado->dado = subtracao_atual;
            subtracao_atual = 0;
        }
    }

    
    return resultado;


}

void realizar_operacao(){
    char tipo_operacao;
    Numero_grande num1,num2;
    scanf(" %c",&tipo_operacao);
    receber_numero(&num1);
    receber_numero(&num2);

    p_no resultado = NULL;
    if(tipo_operacao == '+'){
        resultado = somar(num1,num2);
        imprimir_lista_invertida(resultado);
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