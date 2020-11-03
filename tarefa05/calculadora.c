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

void destruir_lista(p_no lista){
    p_no inicial = lista,aux;
    lista = lista->prox;
    while(lista != inicial){
        aux = lista->prox;
        free(lista);
        lista = aux;
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

p_no somar(Numero_grande num1, Numero_grande num2){
    if(num2.comprimento>num1.comprimento){
        return somar(num2,num1);
    }
    p_no resultado = NULL;
    resultado = adicionar_elemento(resultado,0);
    p_no digito1 = num1.digitos->prox, digito2 = num2.digitos->prox;
    int contador_num2 = 0,soma_atual = 0;

    for(int i = 0; i<num1.comprimento;i++){
        resultado = adicionar_elemento(resultado,0);
        resultado = resultado->prox;
        soma_atual += digito1->dado;
        digito1 = digito1->prox;
        if (contador_num2<num2.comprimento){
            soma_atual += digito2->dado;
            digito2= digito2->prox;
            contador_num2 += 1;
        }
        resultado->dado = (resultado->ant->dado+soma_atual)/10;
        resultado->ant->dado = (resultado->ant->dado+soma_atual)%10;
        soma_atual = 0;
    }
    if(resultado->dado == 0){
        resultado = remover_da_lista(resultado);
    }

    return resultado;
}


p_no subtrair(Numero_grande num1,Numero_grande num2){
    if(num2.comprimento>num1.comprimento){
        return subtrair(num2,num1);
    }
    if(num1.comprimento == num2.comprimento){
        p_no aux1 = num1.digitos, aux2= num2.digitos;
        for(int i = 0;i<num1.comprimento;i++){
            if(aux1->dado <aux2->dado){
                return subtrair(num2,num1);
            }
            if(aux1->dado > aux2->dado){
                break;
            }else{
                aux1 = aux1->ant;
                aux2 = aux2->ant;
            }
        }  
    }
    p_no digito1 = num1.digitos->prox,digito2 = num2.digitos->prox;
    p_no resultado = NULL;
    int subtracao_atual=0,contador_num2 = 0;

    for(int i = 0;i<num1.comprimento;i++){
        resultado = adicionar_elemento(resultado,0);
        resultado = resultado->prox;
        subtracao_atual += digito1->dado;
        digito1 = digito1->prox;

        if(contador_num2<num2.comprimento){
            if(subtracao_atual<digito2->dado){
                resultado->dado = (10 + subtracao_atual - digito2->dado);
                subtracao_atual = -1;
            }else{
                resultado->dado = subtracao_atual - digito2->dado;
                subtracao_atual = 0;
            }
            contador_num2 += 1;
            digito2 = digito2->prox;
        }else{
            resultado->dado = subtracao_atual;
            subtracao_atual = 0;
        }

    }
    for(int i = 0;i<num1.comprimento;i++){
        if(resultado->dado != 0 || resultado->prox == resultado){
            break;
        }else{
            resultado = remover_da_lista(resultado);
        }

    }
    return resultado;

}


p_no multiplicar(Numero_grande num1, Numero_grande num2){

    p_no digito1 =num1.digitos->prox, digito2 = num2.digitos->prox;
    p_no resultado = NULL;
    resultado = adicionar_elemento(resultado,0);
    if(num1.comprimento == 1){ 
        if(digito1->dado == 0){
            return resultado;
        }

    }
    if(num2.comprimento == 1){ 
        if(digito2->dado == 0){
            return resultado;
        }
    }

    for(int i = 0;i<num1.comprimento + num2.comprimento;i++){
        resultado = adicionar_elemento(resultado,0);
    }
    p_no inicial = resultado->ant,aux;

    int multiplicacao_atual = 0;
    int coeficiente ,soma_aux;
    for(int i = 0;i<num1.comprimento;i++){
        coeficiente = digito1->dado;
        for(int j = 0;j<num2.comprimento;j++){
            multiplicacao_atual = coeficiente*(digito2->dado);
            digito2 = digito2->prox;
            aux = resultado;
            soma_aux = aux->ant->dado+multiplicacao_atual;
            do{
                aux->ant->dado = soma_aux%10;
                soma_aux = aux->dado + soma_aux/10;
                aux = aux->prox;
            }while(soma_aux>10);
            aux->ant->dado = (soma_aux);
            resultado = resultado->prox;
        }
        digito1 = digito1->prox;

        resultado = inicial;
        for(int k = 0;k<i+2;k++){
            resultado = resultado->prox;
        }
    }
    resultado = inicial->ant;
    for(int i = 0;i<2;i++){
        if(resultado->dado == 0){
            resultado =  remover_da_lista(resultado);
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

    p_no resultado;
    if(tipo_operacao == '+'){
        resultado = somar(num1,num2);
        imprimir_lista(resultado);
    }
    if(tipo_operacao == '-'){
        resultado = subtrair(num1,num2);
        imprimir_lista(resultado);

    }
    if(tipo_operacao == '*'){
        resultado =  multiplicar(num1,num2);
        imprimir_lista(resultado);
    }
    
    if(tipo_operacao == '/'){
        /*
        dividir(num1,num2);
        */
    }else{
        destruir_lista(resultado);
    }
    
    destruir_lista(num1.digitos);
    destruir_lista(num2.digitos);
    
}


int main(){
    int n;
    scanf("%d",&n);

    for (int i = 0;i<n;i++){
        realizar_operacao();
    }
}