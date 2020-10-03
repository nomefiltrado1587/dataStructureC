#include "professor_carlos.h"
#include <stdio.h>

int ordem_lexicografica(char nome1[],char nome2[]){
    int contador = 0;
        while(nome1[contador]!= '\0' && nome2[contador != '\0']){
        if (nome1[contador] > nome2[contador]){
            return 1;
        } else if(nome1[contador] < nome2[contador]){
            return 0;
        } else{
            contador ++;
        }
    }
    return -1;
}

void comparar_lexicografica(Aluno *mais_novo,Aluno aluno_atual,int *data_aux,int data_atual){
    if (ordem_lexicografica(mais_novo->nome,aluno_atual.nome) == 1){
        *mais_novo = aluno_atual;
        *data_aux = data_atual;
    }else if (ordem_lexicografica(mais_novo->nome,aluno_atual.nome) == -1){
        if (ordem_lexicografica(mais_novo->sobrenome,aluno_atual.sobrenome) == 1){
            *mais_novo = aluno_atual;
            *data_aux = data_atual;
        }
    }
}
Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    Aluno aluno_atual,mais_novo = t[0].alunos[0];
    int data_atual,data_aux = 365*mais_novo.nascimento.ano + 30*mais_novo.nascimento.mes + mais_novo.nascimento.dia;

    for (int i = 0;i<qtd_turmas;i++){
        for(int j = 0;j<t[i].qtd;j++){
            aluno_atual = t[i].alunos[j];
            data_atual = 365*aluno_atual.nascimento.ano + 30*aluno_atual.nascimento.mes + aluno_atual.nascimento.dia;
            if (data_atual > data_aux){
                mais_novo = aluno_atual;
                data_aux = data_atual;
            }else if(data_atual == data_aux){
                comparar_lexicografica(&mais_novo,aluno_atual,&data_aux,data_atual);
            }
        }
    }
    return mais_novo;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    Aluno aluno_atual,mais_velho = t[0].alunos[0];
    int data_atual,data_aux = 365*mais_velho.nascimento.ano + 30*mais_velho.nascimento.mes + mais_velho.nascimento.dia;

    for (int i = 0;i<qtd_turmas;i++){
        for(int j = 0;j<t[i].qtd;j++){
            aluno_atual = t[i].alunos[j];
            data_atual = 365*aluno_atual.nascimento.ano + 30*aluno_atual.nascimento.mes + aluno_atual.nascimento.dia;
            if (data_atual < data_aux){
                mais_velho = aluno_atual;
                data_aux = data_atual;
            }else if(data_atual == data_aux){
                comparar_lexicografica(&mais_velho,aluno_atual,&data_aux,data_atual);
            }
        }
    }
    return mais_velho;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    Aluno aluno_atual,mais_novo = t[j].alunos[0];
    int data_atual,data_aux = 365*mais_novo.nascimento.ano + 30*mais_novo.nascimento.mes + mais_novo.nascimento.dia;

    for(int i = 0;i<t[j].qtd;i++){
        aluno_atual = t[j].alunos[i];
        data_atual = 365*aluno_atual.nascimento.ano + 30*aluno_atual.nascimento.mes + aluno_atual.nascimento.dia;
        if (data_atual > data_aux){
            mais_novo = aluno_atual;
            data_aux = data_atual;
        }else if(data_atual == data_aux){
                comparar_lexicografica(&mais_novo,aluno_atual,&data_aux,data_atual);
            }
    }
    return mais_novo;

}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    Aluno aluno_atual,mais_velho = t[j].alunos[0];
    int data_atual,data_aux = 365*mais_velho.nascimento.ano + 30*mais_velho.nascimento.mes + mais_velho.nascimento.dia;

    for(int i = 0;i<t[j].qtd;i++){
        aluno_atual = t[j].alunos[i];
        data_atual = 365*aluno_atual.nascimento.ano + 30*aluno_atual.nascimento.mes + aluno_atual.nascimento.dia;
        if (data_atual < data_aux){
            mais_velho = aluno_atual;
            data_aux = data_atual;
        }else if(data_atual == data_aux){
                comparar_lexicografica(&mais_velho,aluno_atual,&data_aux,data_atual);
            }
    }
    return mais_velho;
}

int add_aluno(Turma t[], Aluno A, int j){
    int quantidade_alunos = t[j].qtd;
    t[j].alunos[quantidade_alunos] = A;
    t[j].qtd = quantidade_alunos+1;
    return quantidade_alunos + 1;
}

int remove_aluno(Turma t[], int j){
    int quantidade_alunos = t[j].qtd;
    t[j].qtd = quantidade_alunos-1;
    return quantidade_alunos-1;
}

int verificar_string(char nome[15],char padrao[15]){
    int aux, contador=0;
    while(padrao[contador] != '\0'){
        contador ++;
    }
    for (int i = 0;nome[i+contador-1] != '\0';i++){
        aux = 1;
        for (int j = 0;j< contador;j++){
            if (nome[i + j]!=padrao[j]){
                aux = 0;
                break;
            }
        }
        if (aux == 1){
            return 1;
        }
    }
    return 0;
}

int conta_substrings(Turma t[], int qtd_turmas, char padrao[]){
    Turma turma_atual;
    int contador = 0;
    for (int i = 0;i<qtd_turmas;i++){
        turma_atual = t[i];
        for(int j = 0;j<turma_atual.qtd;j++){
            if (verificar_string(turma_atual.alunos[j].nome,padrao) == 1){
                contador ++;
            }
        }
    }
    return contador;
}
