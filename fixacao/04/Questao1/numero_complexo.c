#include <stdio.h>
#include "numero_complexo.h"

Complexo inicializar_numero(double real,double imag){
    Complexo numero;
    numero.parte_real = real;
    numero.parte_imag = imag;
    return numero;
}

void imprimir_numero(Complexo num){
    printf("Parte real : %lf\nParte imaginaria : %lf",num.parte_real,num.parte_imag);
}

Complexo op(Complexo num1,char operacao, Complexo num2){
    Complexo resultado;
    if(operacao == '+'){
        resultado.parte_real = num1.parte_real + num2.parte_real;
        resultado.parte_imag = num1.parte_imag + num2.parte_imag;
    } else if(operacao == '-'){
        resultado.parte_real = num1.parte_real - num2.parte_real;
        resultado.parte_imag = num1.parte_imag - num2.parte_imag;   
    } else if(operacao == '*'){
        resultado.parte_real = num1.parte_real*num2.parte_real-num1.parte_imag*num2.parte_imag;
        resultado.parte_imag = num1.parte_imag*num2.parte_real+num2.parte_imag*num1.parte_real;  
    } else if(operacao == '/'){
        double denominador = (num2.parte_real*num2.parte_real + num2.parte_imag*num2.parte_imag);
        resultado.parte_real = (num1.parte_real*num2.parte_real+num1.parte_imag*num2.parte_imag)/denominador;
        resultado.parte_imag = (num1.parte_imag*num2.parte_real-num2.parte_imag*num1.parte_real)/denominador; 
    } else{
        printf("Operações aceitas : +,-,*,/ \nFica ligado broder");
    }
    return resultado;
}

int comp(Complexo num1,char comparacao, Complexo num2){
    if ('<' != comparacao && comparacao != '>' && comparacao != '='){
        printf("Comparações devem utilizar ""<"" ou "">"" ou ""=""");
        return -1;
    } 
    if (comparacao == '='){
        if (num1.parte_real != num2.parte_real || num1.parte_imag != num2.parte_imag){
            return 0;
        }
        return 1;
    }
    if (num1.parte_imag == 0 && 0 == num2.parte_imag){
        if (comparacao == '>'){
            if (num1.parte_real > num2.parte_real) return 1;
            return 0;
        }
        if (num1.parte_real < num2.parte_real) return 1;
        return 0;
    }
    if (comparacao == '>'){
        if (num1.parte_real*num1.parte_real + num1.parte_imag*num1.parte_imag > num2.parte_real*num2.parte_real + num2.parte_imag*num2.parte_imag) return 1;
        return 0;
    }
    if (num1.parte_real*num1.parte_real + num1.parte_imag*num1.parte_imag < num2.parte_real*num2.parte_real + num2.parte_imag*num2.parte_imag) return 1;
    return 0;
    
}

Complexo obter_conjugado(Complexo num){
    Complexo resultado;
    resultado.parte_real = num.parte_real;
    resultado.parte_imag = num.parte_imag;
    return resultado;
}