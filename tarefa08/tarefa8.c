#include <stdio.h>
#include <stdlib.h>

enum Cor {VERMELHO,PRETO};

typedef struct No {
    enum Cor cor;
    int valor,quantidade;
    struct No *esq,*dir;
}No;

typedef No *p_no;

p_no inicializar_arvore(){
    // CRIA UMA ARVORE VAZIA (O MODELO UTILIZADO FOI RUBRO-NEGRA ESQUERDISTA)
    return NULL;
}

int eh_vermelho(p_no no){
    // CONFERE SE UM NO É VERMELHO ,RETORNANDO 1 PARA SIM E 0 PARA NAO 
    if (no == NULL){
        return 0;
    }
    return no->cor == VERMELHO;
}

int eh_preto(p_no no){
    // CONFERE SE UM NO É PRETO ,RETORNANDO 1 PARA SIM E 0 PARA NAO 
    if (no == NULL){
        return 1;
    }
    return no->cor == PRETO;
}

void sobe_vermelho(p_no raiz){
    //TROCA A COR DA RAIZ PARA VERMELHO E SEUS FILHOS PARA PRETO
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_no rotaciona_para_direita(p_no raiz){
    //COLOCA O FILHO ESQUERDO DA RAIZ NO LUGAR DELA, E ELA VIRA SEU FILHO DIREITO
    int valor_raiz = raiz->valor,quantidade_raiz = raiz->quantidade;
    p_no a = raiz->dir,b = raiz->esq->dir,esquerda = raiz->esq;
    raiz->valor = raiz->esq->valor;
    raiz->quantidade = raiz->esq->quantidade;
    
    raiz->esq = esquerda->esq;
    raiz->dir = esquerda;
    raiz->dir->dir = a;
    raiz->dir->esq = b;
    raiz->dir->valor = valor_raiz;
    raiz->dir->quantidade = quantidade_raiz;

    return raiz;
}

p_no rotaciona_para_esquerda(p_no raiz){
    //COLOCA O FILHO DIREITO DA RAIZ NO LUGAR DEL, E ELA VIRA SEU FILHO ESQUERDO
    int valor_raiz = raiz->valor,quantidade_raiz = raiz->quantidade;
    p_no a = raiz->dir->dir,b = raiz->dir->esq,esquerda = raiz->esq;

    raiz->valor = raiz->dir->valor;
    raiz->quantidade = raiz->dir->quantidade;
    raiz->esq = raiz->dir;
    raiz->esq->valor = valor_raiz;
    raiz->esq->quantidade = quantidade_raiz;
    raiz->esq->esq = esquerda;

    raiz->dir = a;
    raiz->esq->dir = b;
    return raiz;
}

p_no inserir_rec(p_no raiz, int valor) {
    //ISERE UM NOVO VALOR NA RAIZ, E A CORRIGE PARA QUE PERMANÇA RUBRO-NEGRA ESQUERDISTA
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->valor = valor;
        novo->quantidade = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    if (valor < raiz->valor){
        raiz->esq = inserir_rec(raiz->esq, valor);
    }else if  (valor > raiz->valor){
        raiz->dir = inserir_rec(raiz->dir, valor);
    }else{
        raiz->quantidade += 1;
    }


    if (eh_vermelho(raiz->dir) && eh_preto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir))
        sobe_vermelho(raiz);
    return raiz;
}

p_no inserir(p_no raiz, int valor){
    //INSERE UM VALOR EM UMA ARVORE CASO AINDA NAO TENHA SIDO INSERIDO OU AUMENTA SUA QUANTIDADE CASO JA ESTEJA NELA
    raiz = inserir_rec(raiz,valor);
    raiz->cor = PRETO;
    return raiz;
}

int buscar_valor(p_no raiz, int valor){
    //ENCONTRA UM VALOR NA ARVORE E RETORNA SUA QUANTIDADE (OU 0 CASO NAO ESTEJA NA ARVORE)
    if (raiz->valor > valor){
        if (raiz->esq != NULL){
            return buscar_valor(raiz->esq,valor);
        }else{
            return 0;
        }
    }else if (raiz->valor<valor){
        if (raiz->dir != NULL){
            return buscar_valor(raiz->dir,valor);
        }else{
            return 0;
        }
    }else{
        return raiz->quantidade;
    }
}

void operacao3(p_no raiz,int *somatorio){
    // SE A QUANTIDADE DE UM VALOR FOR MAIOR DO QUE ELE SOMA A (QUANTIDADE-VALOR) NO SOMATORIO
    // SE FOR MENOR, SOMA A QUANTIDADE
    if(raiz->esq != NULL){
        operacao3(raiz->esq,somatorio);
    }
    if(raiz->dir != NULL){
        operacao3(raiz->dir,somatorio);
    }
    if (raiz->quantidade != raiz->valor){
        if(raiz->quantidade > raiz->valor){
            *somatorio += raiz->quantidade-raiz->valor;
        }else{
            *somatorio += raiz->quantidade;
        }
    }
}

void liberar_arvore(p_no raiz){
    if (raiz->esq != NULL){
        liberar_arvore(raiz->esq);
    }
    if(raiz->dir != NULL){
        liberar_arvore(raiz->dir);
    }
    free(raiz);
}

int main(){
    int n,k,valor_atual,operacao_atual;
    p_no raiz = inicializar_arvore();

    scanf("%d %d",&n,&k);
    for (int i = 0;i<n;i++){
        scanf(" %d",&valor_atual);
        raiz =  inserir(raiz,valor_atual);
    }

    for(int i = 0;i<k;i++){
        scanf(" %d",&operacao_atual);
        
        if(operacao_atual == 1){
            scanf(" %d",&valor_atual);
            inserir(raiz,valor_atual);
        }else if(operacao_atual == 2){
            scanf(" %d",&valor_atual);
            printf("%d\n",buscar_valor(raiz,valor_atual));
        }else{
            valor_atual = 0;
            operacao3(raiz,&valor_atual);
            printf("%d\n",valor_atual);
        }
    }

    liberar_arvore(raiz);
}