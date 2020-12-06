#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_PALAVRAS 100
#define MAX_PALAVRA 26
#define LETRAS_ALFABETO 26

typedef struct No{
    char palavra[MAX_PALAVRA];
    struct No *prox;
}No;

typedef No *p_no;

typedef struct Hash{
    p_no palavras[100];
}Hash;

void copiar_palavra(char palavra[MAX_PALAVRA],char * local){
    // COPIA UMA PALAVRA
    int i;
    for(i = 0;palavra[i] != '\0';i++){
        local[i]=palavra[i];
    }
    local[i] = '\0';
}

void adicionar_letra(char palavra_base[MAX_PALAVRA],char palavra_resultado[MAX_PALAVRA], char letra, int posicao){
    //COPIA UMA PALAVRA,POREM COM UMA LETRA A MAIS EM DETERMINADA POSIÇÃO
    char aux1,aux2 = palavra_base[posicao];
    int i;
    for(i = 0;i<posicao;i++){
        palavra_resultado[i]=palavra_base[i];
    }
    for(i = posicao;aux2 != '\0';i++){
        aux1 = palavra_base[i+1];
        palavra_resultado[i+1] = aux2;
        aux2 = aux1; 
    }
    palavra_resultado[i+1] = '\0';
    palavra_resultado[posicao] = letra;
}


Hash inicializar_hash(){
    //INICIALIZA UM HASH
    Hash novo;
    for (int i = 0;i<MAX_PALAVRAS;i++){
        novo.palavras[i] = NULL;
    }
    return novo;
}

p_no inserir_na_lista(char palavra[MAX_PALAVRA],p_no no){
    // INSERE UM NOVO NO EM UMA LISTA
    p_no novo = malloc(sizeof(No));
    copiar_palavra(palavra,novo->palavra);
    novo->prox = no;
    return novo;
}

int posicao_no_vetor(char palavra[MAX_PALAVRA] ){
    //DETERMINA A POSIÇÃO QUE DETERMINADA PALAVRA DEVE OCUPAR NO HASH
    double hashing = 0;
    for (int i = 0;palavra[i] != '\0';i++){
        hashing += (int)palavra[i];
    }
    hashing = hashing*(sqrt(5)-1)/2;
    int aux1 = (int)hashing;
    double aux2 = (double)aux1;
    hashing -= aux2;
    hashing = MAX_PALAVRAS*(hashing);
    int resultado = (int)hashing;
    return resultado;
}

void inserir_no_hash(char palavra[MAX_PALAVRA],Hash *hash){
    // INSERE UMA PALAVRA EM UM HASH
    int posicao_no_v = posicao_no_vetor(palavra);
    hash->palavras[posicao_no_v] = inserir_na_lista(palavra,hash->palavras[posicao_no_v]);
}

int comparar_strings(char *str1,char *str2){
    // COMPARA SE DUAS STRINGS SAO IGUAIS
    int eh_igual = 1;
    int i;
    for (i = 0;str1[i] != '\0' && str2[i] != '\0';i++){
        if(str1[i] != str2[i]){
            eh_igual = 0;
            break;
        }
    }
    if(str1[i] != str2[i]){
        eh_igual = 0;
    }
    return eh_igual;
}

int procurar_na_lista(char palavra[MAX_PALAVRA],p_no no){
    //PROCURA UMA PALAVRA EM UMA LISTA E RETORNA 1 CASO TENHA ENCONTRADO
    int achou = 0;
    while(no != NULL && achou != 1){
        achou = comparar_strings(no->palavra,palavra);
        no = no->prox;
    }
    return achou;
}

int procurar_no_hash(char palavra[MAX_PALAVRA],Hash *dicionario){
    //PROCURA UMA PALAVRA EM UM HASH E RETORNA 1 CASO TENHA ENCONTRADO
    int achou = 0;
    achou = procurar_na_lista(palavra,dicionario->palavras[posicao_no_vetor(palavra)]);
    return achou;
}

int procurar_similares(char palavra[MAX_PALAVRA],Hash *dicionario){
    //PROCURA PALAVRAS COM APENAS 1 ERRO EM RELAÇÃO A QUE FOI INSERIDA, SERVE PARA DAR A AVALIAÇÃO "amarela"
    int achou = 0;
    int i;
    char palavra_aux[MAX_PALAVRA];

    //procura palavras com uma letra a mais do que a que foi inserida
    for(i = 0;palavra[i] != '\0' && achou != 1;i++){
        adicionar_letra(palavra,palavra_aux,'a',i);
        for(int j = 0;j<LETRAS_ALFABETO && achou != 1;j++){
            palavra_aux[i] = 'a'+j;
            achou = procurar_no_hash(palavra_aux,dicionario);
        }
    }

    //procura palavras com uma letra a menos do que a palavra que foi inserida
    for(int j = 0;j<MAX_PALAVRA && achou != 1;j++){
        copiar_palavra(palavra,palavra_aux);
        for(int k = j;palavra[k+1]!='\0';k++){
            palavra_aux[k]=palavra[k+2];
        }
        achou = procurar_no_hash(palavra_aux,dicionario);
    }
    
    //troca uma das letras da palavra inserida e a procura
    for(i = 0;palavra[i] != '\0' && achou != 1;i++){
        for(int j = 0;j<LETRAS_ALFABETO && achou != 1;j++){
            palavra[i] = 'a' +(palavra[i] + 1-'a')%LETRAS_ALFABETO;
            achou = procurar_no_hash(palavra,dicionario);
        }
    }
    //procura palavras que tem NO FINAL uma letra a mais do que a que foi inserida
    palavra[i+1] = '\0';
    for(int j = 0;j<LETRAS_ALFABETO && achou != 1;j++){
        palavra[i] = 'a'+j;
        achou = procurar_no_hash(palavra,dicionario);
    }

    return achou;
}

void liberar_lista(p_no no){
    // LIBERA UMA LISTA
    if(no->prox != NULL){
        liberar_lista(no->prox);
    }
    free(no);
}

void liberar_hash(Hash *hash){
    //LIBERA UM HASH
    for (int i = 0;i<MAX_PALAVRAS;i++){
        if(hash->palavras[i] != NULL)   liberar_lista(hash->palavras[i]);
    }
}

int main(){
    Hash dicionario = inicializar_hash();
    int n,q,achou;
    char palavra_atual[MAX_PALAVRA];

    scanf("%d %d", &n,&q);
    for(int i = 0;i<n;i++){
        scanf("%s",palavra_atual);
        inserir_no_hash(palavra_atual,&dicionario);
    }

    for(int j = 0;j<q;j++){
        scanf("%s",palavra_atual);
        achou = 0;
        achou = procurar_no_hash(palavra_atual,&dicionario);

        if (achou == 1){
            printf("verde\n");
        }else{
            achou = procurar_similares(palavra_atual,&dicionario);
            if (achou == 1){
                printf("amarelo\n");
                
            }else{
                printf("vermelho\n");
            }
        }
    }
    liberar_hash(&dicionario);
}