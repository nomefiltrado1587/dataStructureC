#include <stdio.h>
#include <stdlib.h>
#define MAX_PALAVRA 30
#define ERRO -2147483648
#define UNDEFINED -2147483647

typedef struct Grafo{
    int largura;
    int total_termos;
    int **matriz_dependencias;
    int *vertices;
} Grafo;

typedef Grafo * p_grafo;

Grafo inicializar_grafo(){
    // INICIALIZA UM GRAFO
    Grafo grafo;
    grafo.largura = 0;
    grafo.total_termos = 0;
    grafo.matriz_dependencias = NULL;
    grafo.vertices = NULL;
    return grafo;
}

int posicao_x_y(int largura,char x,int y){
    int int_x = (int)(x-'A');
    return int_x+ largura*(y -1);
}

void imprimir_valor(char x,int y,p_grafo planilha){
    int posicao = posicao_x_y(planilha->largura,x,y);
    int valor = planilha->vertices[posicao];
    if(valor == ERRO){
        printf("%c%d: #ERRO#\n",x,y);
    }else{
        printf("%c%d: %d\n",x,y,valor);
    }
}

void receber_parentesis(FILE *arquivo,p_grafo planilha,int posicao,int sinal){
    char letra_atual;
    int numero_do_vertice, acabou = 0;
    int coluna;
    fscanf(arquivo,"%c",&letra_atual);
    
    while(acabou == 0){
        fscanf(arquivo,"%c",&letra_atual);


        if(letra_atual == '-'){
            fscanf(arquivo," %c",&letra_atual);
            if(letra_atual == '('){
                receber_parentesis(arquivo,planilha,posicao,sinal*(-1));
            }else{
                fscanf(arquivo,"%d",&coluna);
                numero_do_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
                planilha->matriz_dependencias[posicao][numero_do_vertice] += -sinal;
            }


        }else if(letra_atual == '('){
            receber_parentesis(arquivo,planilha,posicao,sinal);
        }else if(letra_atual == '+'){
            fscanf(arquivo," %c",&letra_atual);
            if(letra_atual == '('){
                receber_parentesis(arquivo,planilha,posicao,sinal);
            }else{
                fscanf(arquivo,"%d",&coluna);
                numero_do_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
                planilha->matriz_dependencias[posicao][numero_do_vertice] += sinal;
            }
        }else if(letra_atual == ')'){
            acabou = 1;
        }else if(letra_atual != ' '){
            fscanf(arquivo,"%d",&coluna);
            numero_do_vertice = posicao_x_y(planilha->largura,letra_atual,coluna);
            planilha->matriz_dependencias[posicao][numero_do_vertice] += sinal;
        }
    }
}

void ler_termo(FILE *arquivo,p_grafo planilha,int i ,int j, char letra_atual){
    int posicao = i*planilha->largura +j, coluna;
    if (letra_atual != '='){
        fscanf(arquivo, " %d", &(planilha->vertices[posicao]));
    }else{
        planilha->vertices[posicao] = UNDEFINED;
        planilha->matriz_dependencias[posicao] = malloc((planilha->total_termos)*sizeof(int));
        for (int i = 0;i<planilha->total_termos;i++){
            planilha->matriz_dependencias[posicao][i] = 0;
        }
        fscanf(arquivo," %c",&letra_atual);
        if (letra_atual == '('){
            receber_parentesis(arquivo,planilha,posicao,1);
        }else if(letra_atual == '-'){
            fscanf(arquivo," %c",&letra_atual);
            fscanf(arquivo,"%d",&coluna);
            planilha->matriz_dependencias[posicao][posicao_x_y(planilha->largura,letra_atual,coluna)] = -1;
        }else{
            fscanf(arquivo,"%d",&coluna);
            planilha->matriz_dependencias[posicao][posicao_x_y(planilha->largura,letra_atual,coluna)] = 1;
        }
    }
}

int buscar_ciclo(p_grafo planilha,int vertice_buscado,int vertice_atual,int *ja_foram){
    int eh_ciclico = 0;
    /*
    for (int i = 0;i<planilha->total_termos;i++){
        if(planilha->matriz_dependencias[vertice_atual][i] != 0 && ja_foram[i] != 0){
            eh_ciclico = 1;
            break;
        }
    }
    */
    if(planilha->matriz_dependencias[vertice_atual][vertice_buscado] != 0 || planilha->vertices[vertice_atual] == ERRO){
        eh_ciclico = 1;
    }

    if(eh_ciclico){
        /*
        for(int i = 0;i<planilha->total_termos;i++){
            if(ja_foram[i]){
                free(planilha->matriz_dependencias[i]);
                planilha->matriz_dependencias[i] = NULL;
                planilha->vertices[i] = ERRO;
            }
        }
        */
        free(planilha->matriz_dependencias[vertice_buscado]);
        planilha->matriz_dependencias[vertice_buscado] = NULL;
        planilha->vertices[vertice_buscado] = ERRO;
        return 1;
    }

    ja_foram[vertice_atual] = 1;
    if(planilha->matriz_dependencias[vertice_atual] != NULL){
        for (int i = 0;i<planilha->total_termos;i++){
            if(planilha->matriz_dependencias[vertice_atual][i] != 0 && planilha->matriz_dependencias[i] != NULL && ja_foram[i] == 0){
                if(buscar_ciclo(planilha,vertice_buscado,i,ja_foram)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void eh_ciclico(p_grafo planilha, int vertice){
    int *ja_foram = malloc(planilha->total_termos*sizeof(int));
    for (int i = 0;i<planilha->total_termos;i++){
        ja_foram[i] = 0;
    }
    buscar_ciclo(planilha,vertice,vertice,ja_foram);
    free(ja_foram);
}

int buscar_erro(p_grafo planilha,int vertice_buscado,int vertice_atual,int *ja_foram){
    int eh_erro = 0;
    /*
    for (int i = 0;i<planilha->total_termos;i++){
        if(planilha->matriz_dependencias[vertice_atual][i] != 0 && ja_foram[i] != 0){
            eh_erro = 1;
            break;
        }
    }
    */
   for(int i = 0;i<planilha->total_termos;i++){
       if(planilha->matriz_dependencias[vertice_atual][i] != 0 && planilha->vertices[i] == ERRO){
           eh_erro = 1;
       }
   }

    if(eh_erro){
        
        for(int i = 0;i<planilha->total_termos;i++){
            if(ja_foram[i]){
                free(planilha->matriz_dependencias[i]);
                planilha->matriz_dependencias[i] = NULL;
                planilha->vertices[i] = ERRO;
            }
        }
        
        free(planilha->matriz_dependencias[vertice_buscado]);
        planilha->matriz_dependencias[vertice_buscado] = NULL;
        planilha->vertices[vertice_buscado] = ERRO;
        return 1;
    }

    ja_foram[vertice_atual] = 1;
    if(planilha->matriz_dependencias[vertice_atual] != NULL){
        for (int i = 0;i<planilha->total_termos;i++){
            if(planilha->matriz_dependencias[vertice_atual][i] != 0 && planilha->matriz_dependencias[i] != NULL && ja_foram[i] == 0){
                if(buscar_erro(planilha,vertice_buscado,i,ja_foram)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void depende_de_ciclico(p_grafo planilha, int vertice){
    int *ja_foram = malloc(planilha->total_termos*sizeof(int));
    for (int i = 0;i<planilha->total_termos;i++){
        ja_foram[i] = 0;
    }
    buscar_erro(planilha,vertice,vertice,ja_foram);
    free(ja_foram);
}

void alterar_valor(p_grafo planilha,int posicao,int novo_valor){
    int antigo = planilha->vertices[posicao];
    int aux;
    planilha->vertices[posicao] = novo_valor;
    for(int i = 0;i<planilha->total_termos;i++){
        if(planilha->matriz_dependencias[i] != NULL){
            if(planilha->matriz_dependencias[i][posicao] != 0){
                aux = planilha->vertices[i] + (novo_valor-antigo)*planilha->matriz_dependencias[i][posicao];
                alterar_valor(planilha,i,aux);
            }
        }
    }
}

int calcular_vertice(p_grafo planilha, int posicao){
    if(planilha->vertices[posicao] != UNDEFINED){
        return planilha->vertices[posicao];
    }
    int somatorio = 0;

    for(int j = 0;j<planilha->total_termos;j++){
        if(planilha->matriz_dependencias[posicao][j] != 0){
            somatorio += calcular_vertice(planilha,j)*planilha->matriz_dependencias[posicao][j];
        }
    }
    planilha->vertices[posicao] = somatorio;
    return somatorio;
}

int main(){
    int largura,comprimento,valor,total_de_termos,int_y;
    char nome[MAX_PALAVRA],x,operacao_atual,letra_atual;
    Grafo planilha = inicializar_grafo();

    scanf("%s %d %d",nome,&largura,&comprimento);
    planilha.largura = largura;
    planilha.total_termos = largura*comprimento;
    total_de_termos = largura*comprimento;

    planilha.vertices = malloc(total_de_termos*sizeof(int));
    planilha.matriz_dependencias = malloc(total_de_termos*sizeof(int*));

    for (int i = 0 ;i<total_de_termos;i++){
        planilha.matriz_dependencias[i] = NULL;
    }

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

    // DEFINE QUAIS SÃO CICLICOS 
    for(int i = 0;i<total_de_termos;i++){
        if(planilha.vertices[i] == UNDEFINED){
            eh_ciclico(&planilha,i);
        }
    }

    // DEFINE QUAIS DEPENDEM DE CICLICOS
    
    for(int i = 0;i<total_de_termos;i++){
        if(planilha.vertices[i] == UNDEFINED){
            depende_de_ciclico(&planilha,i);
        }
    }
    
    // CALCULA OS QUE SAO DEPENDENTES
    for(int i = 0;i<total_de_termos;i++){
        if(planilha.vertices[i] == UNDEFINED){
            planilha.vertices[i] = 0;
            for(int j = 0;j<total_de_termos;j++){
                if(planilha.matriz_dependencias[i][j] != 0){
                    planilha.vertices[i] += calcular_vertice(&planilha,j)*planilha.matriz_dependencias[i][j];
                }
            }
        }
    } 


    //REALIZA AS OPERAÇÕES
    while(scanf(" %c",&operacao_atual) > 0){
        if (operacao_atual == 'G'){
            scanf(" %c%d",&x,&int_y);
            imprimir_valor(x,int_y,&planilha);
        }else{
            scanf(" %c%d %d",&x,&int_y,&valor);
            int posicao = posicao_x_y(largura,x,int_y);
            printf("%c%d: %d -> %d\n",x,int_y,planilha.vertices[posicao],valor);
            alterar_valor(&planilha,posicao,valor);
        }
    }


}