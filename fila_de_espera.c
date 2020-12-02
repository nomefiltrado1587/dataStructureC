#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_TIPO 15

typedef struct No_int{
    int dado;
    struct No_int *prox;
}No_int;

typedef struct No_int * p_no_int;

typedef struct Paciente{
    char nome[50];
    p_no_int atendimentos;
    int prioritario;
}Paciente;

typedef struct No_paciente {
    Paciente *paciente;
    struct No_paciente *prox;
}No_paciente;

typedef struct No_paciente * p_no_paciente;



p_no_int adicionar_atendimento(p_no_int final_fila,char numero){
    p_no_int novo = malloc(sizeof(No_int));
    if(final_fila != NULL){
        final_fila->prox = novo;
    }
    novo->dado = (int)numero;
    novo->dado -=48;
    novo->prox = NULL;
    return novo;
}

p_no_int remover_atendimento(Paciente *paciente){
    p_no_int aux = paciente->atendimentos->prox;
    free(paciente->atendimentos);
    return aux;
}

p_no_paciente fila_normal(p_no_paciente final_fila,Paciente *paciente){
    p_no_paciente novo = malloc(sizeof(No_paciente));
    if(final_fila != NULL){
        final_fila->prox = novo;
    }
    novo->prox = NULL;
    novo->paciente = paciente;
    return novo;
}


p_no_paciente fila_prioritario(p_no_paciente inicio_fila,Paciente *paciente){
    p_no_paciente novo = malloc(sizeof(No_paciente));
    novo->prox = inicio_fila;
    novo->paciente = paciente;
    return novo;
}

p_no_paciente atender_paciente(p_no_paciente no_paciente,int relogio,p_no_paciente filas[20]){
    p_no_paciente prox = no_paciente->prox;
    printf("prox = %p\n",prox);
    Paciente *paciente_atual = no_paciente->paciente;
    p_no_int dale = paciente_atual->atendimentos;
    while(dale != NULL){
        printf("AAA %d\n",dale->dado);
        dale = dale->prox;
    }
    printf("BBB\n");
    if (paciente_atual->atendimentos == NULL){
        printf("RELOGIO: %d\n",10*(relogio%6));
    }else{
        if (paciente_atual->prioritario == 1){
            filas[2*paciente_atual->atendimentos->dado] = fila_prioritario(filas[2*paciente_atual->atendimentos->dado ],paciente_atual);
            paciente_atual->atendimentos = remover_atendimento(paciente_atual);
        }else{
            filas[2*paciente_atual->atendimentos->dado+1] = fila_normal(filas[2*paciente_atual->atendimentos->dado+1],paciente_atual);
            paciente_atual->atendimentos = remover_atendimento(paciente_atual);
        }
    }
    return prox;

}
int todas_vazias(p_no_paciente filas[20]){
    for (int i = 0;i<20;i+=2){
        if (filas[i] != NULL){
            return 0;
        }
    }
    return 1;
}


int main(){

    char tipo[MAX_TIPO],letra_atual;
    int i =0 ,nao_acabou_arquivo;

    p_no_paciente filas[20];
    for(int i = 0;i<20;i++){
        filas[i] = NULL;
    }

    do{
        nao_acabou_arquivo = 1;
        Paciente *paciente_atual = malloc(sizeof(Paciente));
        paciente_atual ->atendimentos = NULL;
        scanf(" %c",&letra_atual);
        do{
            scanf("%c",&letra_atual);
            paciente_atual->nome[i] = letra_atual;
            i+=1;
        }while(letra_atual != '"');
        paciente_atual->nome[i-1] = '\0';

        scanf(" %s",tipo);
        scanf(" %c",&letra_atual);
        if (tipo[0] == 'n'){
            paciente_atual->prioritario = 0;
            if (filas[2*(letra_atual-48) ] == NULL){
                filas[2*(letra_atual-48) +1] = fila_normal(filas[2*(letra_atual-48) +1],paciente_atual);
                filas[2*(letra_atual-48) ] = filas[2*(letra_atual-48) +1];
            }else{
                filas[2*(letra_atual-48) +1] = fila_normal(filas[2*(letra_atual-48) ],paciente_atual);
            }
        }else{
            paciente_atual->prioritario = 1;
            if(filas[2*(letra_atual-48) ] == NULL){
                filas[2*(letra_atual-48)] = fila_prioritario(filas[2*(letra_atual-48) ],paciente_atual);
                filas[2*(letra_atual-48)+1] = filas[2*(letra_atual-48) ];
            }else{
                filas[2*(letra_atual-48) ] = fila_prioritario(filas[2*(letra_atual-48) ],paciente_atual);
            }
        }

        p_no_int inicial = adicionar_atendimento(NULL,letra_atual);
        paciente_atual->atendimentos = inicial;
        scanf(" %c",&letra_atual);
        
        while(letra_atual != '"' && nao_acabou_arquivo == 1){
            paciente_atual->atendimentos = adicionar_atendimento(paciente_atual->atendimentos,letra_atual);
            nao_acabou_arquivo = scanf(" %c",&letra_atual);
        }
        paciente_atual->atendimentos = inicial;
    letra_atual = 'a';
    }while( nao_acabou_arquivo == 1);

    for(int i = 0;i<20;i++){
        p_no_paciente atual = filas[i];
        while(atual!= NULL){
            printf("%d \n",atual->paciente->prioritario);
            atual = atual->prox;
        }
    }
    









    int medicos_especialidade[9] = {10,2,5,3,4,7,2,1,4};
    //ELEMENTOS 2*i SÃO OS INÍCIOS DAS FILAS, 2*i+1 OS FINAIS
    
    int relogio = 0;
    while(todas_vazias(filas) == 0){
        relogio += 1;
        for(int i = 0;i<9;i++){
            for(int j = 0;j<medicos_especialidade[i];j++){
                if(filas[2*i] != NULL){
                    filas[2*i] = atender_paciente(filas[2*i],relogio,filas);
                }else{
                    break;
                }


            }
        }
    }
    
    
}