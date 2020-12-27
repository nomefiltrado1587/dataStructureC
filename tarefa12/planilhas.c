#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"
#define MAX_PALAVRA 30
#define ERRO -2147483648
#define UNDEFINED -2147483647


int posicao_x_y(int largura,char x,int y){
    // CALCULA A POSIÇÃO QUE UMA CÉLULA TEM NO VETOR DO GRAFO
    // A PARTIR DE SUAS COORDENADAS x E y
    int int_x = (int)(x-'A');
    return int_x+ largura*(y -1);
}

void imprimir_valor(char x,int y,p_grafo planilha){
    //IMPRIME O VALOR DE UMA CELULA
    int posicao = posicao_x_y(planilha->largura,x,y);
    int valor = planilha->vertices[posicao].valor;
    if(valor == ERRO){
        printf("%c%d: #ERRO#\n",x,y);
    }else{
        printf("%c%d: %d\n",x,y,valor);
    }
}
void receber_parentesis(FILE *arquivo,p_grafo planilha,int posicao,int sinal);

void receber_expressao(FILE *arquivo,p_grafo p,int posicao,int sinal,char letra ){
    // AUXILIA EM receber_parentesis
    int coluna, numero_do_vertice;
    if(letra == '('){
        receber_parentesis(arquivo,p,posicao,sinal);
    }else{
        fscanf(arquivo,"%d",&coluna);
        numero_do_vertice = posicao_x_y(p->largura,letra,coluna);
        adicionar_dependencia(p, posicao,numero_do_vertice,sinal);
    }
}

void receber_parentesis(FILE *arquivo,p_grafo planilha,int posicao,int sinal){
    // ARMAZENA AS RELAÇÕES ENTRE CELULAS CONTIDAS EM UM PARENTESIS DE FORMA RECURSIVA
    char letra_atual;
    int numero_do_vertice, acabou = 0;
    int coluna;
    fscanf(arquivo,"%c",&letra_atual);
    while(acabou == 0){
        fscanf(arquivo,"%c",&letra_atual);
        if(letra_atual == '-'){
            fscanf(arquivo," %c",&letra_atual);
            receber_expressao(arquivo,planilha,posicao,-sinal,letra_atual);
        }else if(letra_atual == '('){
            receber_parentesis(arquivo,planilha,posicao,sinal);
        }else if(letra_atual == '+'){
            fscanf(arquivo," %c",&letra_atual);
            receber_expressao(arquivo,planilha,posicao,sinal,letra_atual);
        }else if(letra_atual == ')'){
            acabou = 1;
        }else if(letra_atual != ' '){
            fscanf(arquivo,"%d",&coluna);
            numero_do_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
            adicionar_dependencia(planilha, posicao,numero_do_vertice,sinal);
        }
    }
}

void ler_termo(FILE *arquivo,p_grafo planilha,int i ,int j, char letra_atual){
    // LE UM TERMO DO ARQUIVO .csv
    int posicao = i*planilha->largura +j, coluna,numero_vertice;
    if (letra_atual != '='){
        fscanf(arquivo, " %d", &(planilha->vertices[posicao].valor));
    }else{
        planilha->vertices[posicao].valor = UNDEFINED;
        fscanf(arquivo," %c",&letra_atual);
        if (letra_atual == '('){
            receber_parentesis(arquivo,planilha,posicao,1);
        }else if(letra_atual == '-'){
            fscanf(arquivo," %c",&letra_atual);
            fscanf(arquivo,"%d",&coluna);
            numero_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
            adicionar_dependencia(planilha,posicao,numero_vertice,-1);
        }else{
            fscanf(arquivo,"%d",&coluna);
            numero_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
            adicionar_dependencia(planilha,posicao,numero_vertice,1);
        }
    }
}

int buscar_ciclo(p_grafo planilha,int vertice_buscado,int vertice_atual,int *ja_foram){
    // CONFERE RECURSIVAMENTE SE UM VERTICE FAZ PARTE DE UM CICLO
    if(eh_dependente(planilha, vertice_atual,vertice_buscado)){
        planilha->vertices[vertice_buscado].valor = ERRO;
        return 1;
    }
    if(planilha->vertices[vertice_atual].valor == ERRO){
        planilha->vertices[vertice_buscado].valor = ERRO;
        return 1;
    }
    ja_foram[vertice_atual] = 1;
    int filho;
    for(p_lista aux = planilha->vertices[vertice_atual].pais ; aux!=NULL ; aux=aux->prox){
        filho = aux->vertice;
        if(ja_foram[filho] == 0 && planilha->vertices[filho].pais != NULL){
            if( buscar_ciclo(planilha,vertice_buscado,filho,ja_foram) ){
                return 1;
            }
        }
    }
    return 0;
}

void eh_ciclico(p_grafo planilha, int vertice){
    // CONFERE SE UM VERTICE É CICLICO, CASO SIM, O DEFINE COMO ERRO
    int *ja_foram = malloc(planilha->total_termos*sizeof(int));
    for (int i = 0;i<planilha->total_termos;i++){
        ja_foram[i] = 0;
    }
    buscar_ciclo(planilha,vertice,vertice,ja_foram);
    free(ja_foram);
}

int buscar_erro(p_grafo planilha,int vertice_buscado,int vertice_atual,int *ja_foram){
    // CONFERE DE FORMA RECURSIVA SE UMA CELULA DEPENDE DE ALGUMA QUE SEJA UM ERRO
    int eh_erro = 0;
   for(int i = 0;i<planilha->total_termos;i++){
       if(eh_dependente(planilha, vertice_atual,i) && planilha->vertices[i].valor == ERRO){
           eh_erro = 1;
       }
   }
    if(eh_erro){
        for(int i = 0;i<planilha->total_termos;i++){
            if(ja_foram[i]){
                planilha->vertices[i].valor = ERRO;
            }
        }
        planilha->vertices[vertice_buscado].valor = ERRO;
        return 1;
    }

    ja_foram[vertice_atual] = 1;
    int filho;
    for(p_lista aux = planilha->vertices[vertice_atual].pais ; aux!=NULL ; aux=aux->prox){
        filho = aux->vertice;
        if(ja_foram[filho] == 0 && planilha->vertices[filho].pais != NULL){
            if(buscar_erro(planilha,vertice_buscado,filho,ja_foram) ){
                return 1;
            }
        }
    }
    return 0;
}

void depende_de_ciclico(p_grafo planilha, int vertice){
    //CONFERE SE UMA CELULA DEPENDE DE ALGUMA QUE ESTEJA MARCADA COMO ERRO
    int *ja_foram = malloc(planilha->total_termos*sizeof(int));
    for (int i = 0;i<planilha->total_termos;i++){
        ja_foram[i] = 0;
    }
    buscar_erro(planilha,vertice,vertice,ja_foram);
    free(ja_foram);
}

void alterar_valor(p_grafo planilha,int posicao,int novo_valor){
    // ALTERA O VALOR DE UMA CELULA, E DE TODAS QUE DEPENDEM DELA DE FORMA RECURSIVA
    int antigo = planilha->vertices[posicao].valor;
    int variacao = (novo_valor-antigo), aux;
    planilha->vertices[posicao].valor = novo_valor;
    p_lista filhos;
    for(filhos = planilha->vertices[posicao].filhos;filhos != NULL;filhos = filhos->prox){
        if(planilha->vertices[filhos->vertice].valor != ERRO){
            aux = planilha->vertices[filhos->vertice].valor;
            alterar_valor(planilha,filhos->vertice, aux + filhos->dependencia*(variacao));
        }
    }
}

int calcular_vertice(p_grafo planilha, int posicao){
    // CALCULA O VALOR DE UM VERTICE E DE SEUS PAIS (CASO AINDA ESTEJAM INDEFINIDOS)
    if(planilha->vertices[posicao].valor != UNDEFINED){
        return planilha->vertices[posicao].valor;
    }
    int somatorio = 0;
    p_lista pais;
    for(pais = planilha->vertices[posicao].pais;pais != NULL;pais = pais->prox){
        somatorio += calcular_vertice(planilha,pais->vertice)*pais->dependencia;
    }
    planilha->vertices[posicao].valor = somatorio;
    return somatorio;
}

void calcular_vertices_indefinidos(p_grafo planilha, int total_de_termos){
    // DEFINE QUAIS SÃO CICLICOS 
    for(int i = 0;i<total_de_termos;i++){
        if(planilha->vertices[i].valor == UNDEFINED){
            eh_ciclico(planilha,i);
        }
    }

    // DEFINE QUAIS DEPENDEM DE CICLICOS
    for(int i = 0;i<total_de_termos;i++){
        if(planilha->vertices[i].valor == UNDEFINED){
            depende_de_ciclico(planilha,i);
        }
    }
    
    // CALCULA OS QUE SAO DEPENDENTES
    int soma_atual;
    for(int i = 0;i<total_de_termos;i++){
        if(planilha->vertices[i].valor == UNDEFINED){
            planilha->vertices[i].valor = 0;
            for(p_lista pais = planilha->vertices[i].pais;pais != NULL;pais = pais->prox){
                soma_atual = calcular_vertice(planilha,pais->vertice);
                planilha->vertices[i].valor += soma_atual*pais->dependencia;
            }
        }
    }
}

int main(){
    int largura,comprimento,valor,total_de_termos,int_y;
    char nome[MAX_PALAVRA],x,operacao_atual,letra_atual;

    scanf("%s %d %d",nome,&largura,&comprimento);
    total_de_termos = largura*comprimento;
    Grafo planilha = inicializar_grafo(total_de_termos,largura);

    FILE *arquivo = fopen(nome, "r");

    //RECEBE A PLANILHA
    fscanf(arquivo, "%c",&letra_atual);
    for(int i = 0;i<comprimento;i++){
        for(int j = 0;j<largura;j++){
            ler_termo(arquivo,&planilha,i,j,letra_atual);
            fscanf(arquivo, "%c%c%c",&letra_atual,&letra_atual,&letra_atual);
        }
    }
    fclose(arquivo);

    calcular_vertices_indefinidos(&planilha,total_de_termos);

    //REALIZA AS OPERAÇÕES
    while(scanf(" %c",&operacao_atual) > 0){
        if (operacao_atual == 'G'){
            scanf(" %c%d",&x,&int_y);
            imprimir_valor(x,int_y,&planilha);
        }else{
            scanf(" %c%d %d",&x,&int_y,&valor);
            int posicao = posicao_x_y(largura,x,int_y);
            printf("%c%d: %d -> %d\n",x,int_y,planilha.vertices[posicao].valor,valor);
            alterar_valor(&planilha,posicao,valor);
        }
    }

    liberar_grafo(&planilha);
}