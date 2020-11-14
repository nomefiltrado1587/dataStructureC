#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_TIPO 15
#define N_ESPECIALIDADES 9
#define MAX_NOVOS_ATENDIMENTOS 38

typedef struct No_int{
    int dado;
    struct No_int *prox;
}No_int;

typedef struct No_int * p_no_int;

typedef struct Paciente{
    char *nome;
    p_no_int atendimentos;
    int prioritario,chegada;
}Paciente;

typedef struct No_paciente {
    Paciente *paciente;
    struct No_paciente *prox;
}No_paciente;

typedef struct No_paciente * p_no_paciente;


p_no_int adicionar_na_fila_int(p_no_int ant,int especialidade){
    p_no_int novo = malloc(sizeof(int));
    if (ant != NULL){
        ant->prox = novo;
    }
    novo->dado = especialidade;
    return novo;
}


void adicionar_na_fila_pac(Paciente *paciente,p_no_paciente filas[2*N_ESPECIALIDADES],int especialidade){
    p_no_paciente novo = malloc(sizeof(No_paciente));
    novo->paciente = paciente;
    if (filas[especialidade] == NULL){
        filas[especialidade] = novo;
        filas[especialidade+1] = novo;
    }else{
        if(paciente->prioritario == 0){
            filas[especialidade+1]->prox = novo;
            filas[especialidade+1] = novo;
            filas[especialidade+1]->prox = NULL;
        }else{
            p_no_paciente aux = filas[especialidade];
            filas[especialidade] = novo;
            filas[especialidade]->prox = aux;
        }
    }
}

char *receber_nome(){
    char letra_atual;
    int i = 0;
    char *nome = malloc(MAX_NOME*sizeof(char));
    do{
        scanf("%c",&letra_atual);
        nome[i] = letra_atual;
        i+=1;
    }while(letra_atual != '"');
    nome[i-1] = '\0';
    return nome;
}

int receber_tipo(){
    char tipo[15];
    scanf(" %s",tipo);
    if (tipo[0] == 'n'){
        return 0;
    }
    return 1;
}

p_no_int receber_atendimentos(Paciente *paciente_atual,int *arquivo_nao_acabou,p_no_paciente filas[2*N_ESPECIALIDADES]){

    char letra_atual;
    scanf(" %c ",&letra_atual);
    adicionar_na_fila_pac(paciente_atual,filas,2*(letra_atual-49));

    p_no_int no_atual = NULL, inicial=NULL;
    *arquivo_nao_acabou = scanf(" %c",&letra_atual);
    if(letra_atual != '"' && *arquivo_nao_acabou == 1 ){
        no_atual = adicionar_na_fila_int(no_atual,2*(letra_atual-49));
        inicial = no_atual;
    }
    if(*arquivo_nao_acabou == 1 && letra_atual != '"'){
        *arquivo_nao_acabou = scanf(" %c",&letra_atual);
    }
    while(*arquivo_nao_acabou == 1 && letra_atual != '"'){
        no_atual = adicionar_na_fila_int(no_atual,2*(letra_atual-49));
        *arquivo_nao_acabou = scanf(" %c",&letra_atual);
    }

    return inicial;
}

int todas_vazias(p_no_paciente listas[2*N_ESPECIALIDADES]){
    for(int i = 0;i< 2*N_ESPECIALIDADES;i++){
        if(listas[i] != NULL){
            return 0;
        }
    }
    return 1;
}

void liberar_paciente(Paciente *paciente_atual,int relogio){
    if(relogio<12){
        printf("0");
    }
    printf("%d:",8+relogio/6);
    if(relogio%6 == 0){
        printf("00 ");
    }else{
        printf("%d0 ",relogio%6);
    }
    printf("%s\n",paciente_atual->nome);
    free(paciente_atual->nome);
    free(paciente_atual);
}

void atender_paciente(int aux,p_no_paciente filas[2*N_ESPECIALIDADES],int relogio,int *contador,Paciente *novas_consultas[MAX_NOVOS_ATENDIMENTOS]){
    p_no_paciente no_atual = filas[aux];
    Paciente *paciente_atual = no_atual->paciente;
    // REMOVE DA FILA DE ATENDIMENTO
    if (no_atual->prox == NULL){
        filas[aux] = NULL;
        filas[aux+1] = NULL;
    }else{
        filas[aux] = no_atual->prox;
    }

    if (paciente_atual->atendimentos == NULL){
        liberar_paciente(paciente_atual,relogio);
        free(no_atual);
    }else{
        novas_consultas[*contador] = paciente_atual;
        *contador += 1;
    }
     
    
}

void imprimir_lista(p_no_paciente aux1){
    while (aux1 != NULL){
        p_no_int aux2 = aux1->paciente->atendimentos;
        printf("%s",aux1->paciente->nome);
        while(aux2 != NULL){
            printf(" %d",aux2->dado/2 +1);
            aux2 = aux2->prox;
        }
        aux1 = aux1->prox;
        printf("\n");
    }
}

void imprimir_pacientes(p_no_paciente filas[2*N_ESPECIALIDADES]){
    for(int i = 0;i<2*N_ESPECIALIDADES;i+=2){
        printf("%d:\n",i/2 +1);
        imprimir_lista(filas[i]);
        printf("\n");
    }
    printf("\nCABOU\n");
}

void adicionar_novas_consultas(Paciente *novas_consultas[MAX_NOVOS_ATENDIMENTOS],p_no_paciente filas[2*N_ESPECIALIDADES]){
    int especialidade , i = 0;
    while(novas_consultas[i] != NULL){
        //printf("AQUI %d %d\n",paciente_atual->atendimentos->dado,paciente_atual->prioritario);
        especialidade = novas_consultas[i]->atendimentos->dado;
        
    
        p_no_int atendimento_atual = novas_consultas[i]->atendimentos;
        novas_consultas[i]->atendimentos = novas_consultas[i]->atendimentos->prox;
        free(atendimento_atual);
        
        
        adicionar_na_fila_pac(novas_consultas[i],filas,especialidade);
        i+=1;
    }
}

int comparar(const void *p1,const void *p2){
    const Paciente **P1 = (const Paciente **)p1;
    const Paciente **P2 = (const Paciente **)p2;
    return ((*P1)->chegada - (*P2)->chegada);
}


int main(){
    int arquivo_nao_acabou = 1;

    p_no_paciente filas[2*N_ESPECIALIDADES];
    for(int i = 0;i<2*N_ESPECIALIDADES;i++){
        filas[i] = NULL;
    // filas[2*i] É O INICIO DE UMA FILA DE PACIENTES E filas[2*i+1] O FIM
    }

    char aux;
    int contador = 0;
    scanf(" %c",&aux);
    while(arquivo_nao_acabou == 1){
        contador += 1;
        Paciente *paciente_atual = malloc(sizeof(Paciente));
        paciente_atual->chegada = contador;
        paciente_atual->nome = receber_nome();
        paciente_atual->prioritario = receber_tipo();
        paciente_atual->atendimentos = receber_atendimentos(paciente_atual,&arquivo_nao_acabou,filas);
    }
    

    /*
    for(int i = 0;i<2*N_ESPECIALIDADES;i++){
        if (filas[i] != NULL){
        printf("%d %s\n",i,filas[i]->paciente->nome);
        }
    }*/
    
    int medicos_por_especialidade[9] = {10,2,5,3,4,7,2,1,4};
    int relogio = 1;
    Paciente *novas_consultas[MAX_NOVOS_ATENDIMENTOS];
    do{
        contador = 0;
        novas_consultas[0] = NULL;
        for(int i = 0;i<N_ESPECIALIDADES;i++){
            for(int j = 0;j<medicos_por_especialidade[i];j++){
                if(filas[2*i] != NULL){
                    //imprimir_pacientes(filas);
                    //printf("-//-//-\n");
                    atender_paciente(2*i,filas,relogio,&contador,novas_consultas);
                }else{
                    break;
                }
            }
            //imprimir_lista(filas[16]);
        }
        novas_consultas[contador] = NULL;

        while(novas_consultas[contador] != NULL){
            contador += 1;
        }


        qsort(novas_consultas,contador,sizeof(p_no_paciente),comparar);

        adicionar_novas_consultas(novas_consultas,filas);
        relogio += 1;
    }while(todas_vazias(filas) == 0);
    
    
}