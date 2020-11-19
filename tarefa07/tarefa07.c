#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 2048

typedef struct No{
    int valor;
    char *mensagem;
    struct No *esq,*dir;
}No;

typedef No *p_no;

void liberar_arvore(p_no raiz){
    // DESALOCA COMPLETAMENTE UMA ARVORE BINARIA
    if(raiz->dir != NULL){
        liberar_arvore(raiz->dir);
    }
    if(raiz->esq != NULL){
        liberar_arvore(raiz->esq);
    }
    free(raiz->mensagem);
    free(raiz);
}

p_no inserir(p_no raiz, int valor, char *mensagem) {
    //INSERE UM NOVO ELEMENTE EM UMA ARVORE BINARIA DE BUSCA
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;
        novo->mensagem = mensagem;
    return novo;
    }
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor,mensagem);
    else
        raiz->dir = inserir(raiz->dir, valor,mensagem);
    return raiz;
}

p_no receber_tokens_entrada(p_no raiz){
    //LE OS VALORES E MENSAGENS DE CADA TOKEN E OS ARMAZENA EM UMA ARVORE DE BUSCA ATRAVES DA FUNÇÃO inserir()
    char aspas,letra_atual, *mensagem_atual = malloc(MAX_STRING*sizeof(char));
    int contador,valor_atual;
    scanf(" %d ",&valor_atual);
    scanf("%c",&aspas);
    scanf("%c",&letra_atual);
    contador = 0;
    while(letra_atual != '"'){
        mensagem_atual[contador] = letra_atual;
        contador+= 1;
        scanf("%c",&letra_atual);
    }
    mensagem_atual[contador]= '\0';
    raiz = inserir(raiz,valor_atual,mensagem_atual);
    return raiz;
}

p_no buscar_no(p_no raiz, int valor){
    // BUSCA UM VALOR EM UMA ARVORE BINARIA DE BUSCA, E RETORNA UM PONTEIRO PARA O NO QUE O CONTEM
    while (raiz != NULL && valor != raiz->valor)
    if (valor < raiz->valor)
    raiz = raiz->esq;
    else
    raiz = raiz->dir; 
    if (raiz == NULL){
        return NULL;
    }
    return raiz;
}

void remover_sucessor(p_no raiz) {
    //  AUXILIA A FUNÇÃO remover_rec(), ENCONTRANDO E RETORNANDO AS INFORMAÇÕES NOVAS DO NÓ QUE SERÁ "REMOVIDO" 
    p_no min = raiz->dir;
    p_no pai = raiz;
    while (min->esq != NULL) {
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;
    raiz->valor = min->valor;
    raiz->mensagem = min->mensagem;
    free(min);
}


p_no remover_rec(p_no raiz, int valor) {
    //REMOVE O NO QUE CONTEM DETERMINADA CHAVE EM UMA LISTA
    if (raiz == NULL)
        return NULL;
    if (valor < raiz->valor)
        raiz->esq = remover_rec(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover_rec(raiz->dir, valor);
    else {
        free(raiz->mensagem);
        if (raiz->esq == NULL){
            p_no aux = raiz->dir;
            free(raiz);
            return aux;
            }
        else if (raiz->dir == NULL){
            p_no aux = raiz->esq;
            free(raiz);
            return aux;
            }
        else
            remover_sucessor(raiz);
    }
    return raiz;
}

void imprimir_arvore(p_no raiz){
    //IMPRIME AS MENSAGENS CONTIDAS EM UMA ARVORE BINARIA, DA CHAVE MENOR PARA A MAIOR (ORDEM CRESCENTE)
    if(raiz->esq != NULL){
        imprimir_arvore(raiz->esq);
    }
    printf("%s",raiz->mensagem);
    if(raiz->dir != NULL){
        imprimir_arvore(raiz->dir);
    }
}

void testar_valores(int soma2 ,p_no raiz_inicial,p_no raiz_atual,p_no *no1,p_no *no2,p_no *no3,int *tripla_encontrada){
    // AUXILIA A FUNÇÃO encontrar_tripla(), ENCONTRANDO NO2 E NO3 TAIS QUE (chave1+chave2+chave3 = hierarquia)
    if(*tripla_encontrada == 0){
        *no2 = raiz_atual;
        if(*no1 != *no2){
            *no3 = buscar_no(raiz_inicial,soma2-(*no2)->valor);
            if(*no3 != NULL && *no3 != *no2 && *no3 != *no1){
                *tripla_encontrada = 1;
            }
        }
        if(*tripla_encontrada == 0){
            if(raiz_atual->esq != NULL){
                testar_valores(soma2,raiz_atual->esq,raiz_inicial,no1,no2,no3,tripla_encontrada);
            }
            if(raiz_atual->dir != NULL && soma2-raiz_atual->valor>0){
                testar_valores(soma2,raiz_atual->dir,raiz_inicial,no1,no2,no3,tripla_encontrada);
            }
        }
    }
}

void encontrar_tripla(int soma,p_no raiz_inicial,p_no raiz_atual,p_no *no1,p_no *no2,p_no *no3,int *tripla_encontrada){
    // ENCONTRA UMA TRIPLA QUE SOMADA DE A HIERARQUIA, E GUARDA OS NOS no1,no2,no3 ATRAVES DE PONTEIROS PARA ELES
    if(*tripla_encontrada == 0){
        *no1 = raiz_atual;
        testar_valores(soma - raiz_atual->valor,raiz_inicial,raiz_inicial,no1,no2,no3,tripla_encontrada);
        if(*tripla_encontrada == 0){
            if(raiz_atual->esq != NULL){
                encontrar_tripla(soma,raiz_inicial,raiz_atual->esq,no1,no2,no3,tripla_encontrada);
            }
            if(raiz_atual->dir != NULL){
                encontrar_tripla(soma,raiz_inicial,raiz_atual->dir,no1,no2,no3,tripla_encontrada);
            }
        }
    }
}

char * criar_mensagem(p_no no1,p_no no2,p_no no3){
    // CONCATENA AS MENSAGENS DE 3 NOS E RETORNA UM PONTEIRO PARA ELA
    char *nova_mensagem = malloc(sizeof(char)*MAX_STRING);
    int contador_nova = 0,contador = 0;
    while(no1->mensagem[contador] != '\0'){
        nova_mensagem[contador_nova] = no1->mensagem[contador];
        contador_nova += 1;
        contador += 1;
    }
    contador = 0;
    while(no2->mensagem[contador] != '\0'){
        nova_mensagem[contador_nova] = no2->mensagem[contador];
        contador_nova += 1;
        contador += 1;
    }
    contador = 0;
    while(no3->mensagem[contador] != '\0'){
        nova_mensagem[contador_nova] = no3->mensagem[contador];
        contador_nova += 1;
        contador += 1;
    }
    nova_mensagem[contador_nova] = '\0';
    return nova_mensagem;
}

p_no receber_novo_token(p_no raiz,p_no no1,p_no no2,p_no no3,int autoridade){
    // INSERE O NOVO TOKEN E REMOVE OS 3 QUE O DERAM ORIGEM
    int valor1 = no1->valor,valor2 = no2->valor,valor3 = no3->valor;
    raiz = inserir(raiz,autoridade,criar_mensagem(no1,no2,no3));
    if(no1->valor+no2->valor+no3->valor != autoridade){
    }
    raiz = remover_rec(raiz,valor1);
    raiz = remover_rec(raiz,valor2);
    raiz = remover_rec(raiz,valor3);

    return raiz;
}

p_no atualizar_arvore(p_no raiz,p_no no1,p_no no2,p_no no3,int autoridade){
    // ATUALIZA A ARVORE A PARTIR DE UMA TRIPLA
    if(no2->valor <no3->valor){
        if(no1->valor<no2->valor){
            raiz = receber_novo_token(raiz,no1,no2,no3,autoridade);
        }else if(no1->valor<no3->valor){
            raiz = receber_novo_token(raiz,no2,no1,no3,autoridade);
        }else{
            raiz = receber_novo_token(raiz,no2,no3,no1,autoridade);
        }
    }else{
        if(no1->valor<no3->valor){
            raiz = receber_novo_token(raiz,no1,no3,no2,autoridade);
        }else if(no1->valor<no2->valor){
            raiz = receber_novo_token(raiz,no3,no1,no2,autoridade);
        }else{
            raiz = receber_novo_token(raiz,no3,no2,no1,autoridade);
        } 
    }
    return raiz;
}


int main(){

    int arquivo_nao_acabou = 1,n,m,autoridade;
    p_no raiz = NULL;

    scanf("%d %d",&n,&m);
    while (arquivo_nao_acabou != -1){

        raiz = NULL;
        for(int i = 0;i<n;i++){
            raiz = receber_tokens_entrada(raiz);
        }

        for(int i = 0;i<m;i++){
            arquivo_nao_acabou = scanf(" %d",&autoridade);
            
            p_no no1,no2,no3; 
            int tripla_encontrada = 0; // CASO A TRIPLA TENHA SIDO ENCONTRADA, SERVE PARA PARAR O PROCESSO DE BUSCA PELA TRIPLA
            encontrar_tripla(autoridade,raiz,raiz,&no1,&no2,&no3,&tripla_encontrada);
            raiz = atualizar_arvore(raiz,no1,no2,no3,autoridade);
        }

        imprimir_arvore(raiz);
        printf("\n");

        liberar_arvore(raiz);
        
        arquivo_nao_acabou =  scanf("%d %d",&n,&m);
    }
}