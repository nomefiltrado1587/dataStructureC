#include <stdio.h>
#include <stdlib.h>
#define MAX_NOME 15
#define MAX_PASSAGEIROS 500

typedef struct Passageiro {
    char *nome;
    double avaliacao;
    int x_passageiro,y_passageiro;
    int x_destino,y_destino;
}Passageiro;

typedef Passageiro *p_passageiro;

typedef struct Heap{
    p_passageiro *passageiros;
    int n;
    int max;
}Heap;

int modulo(int x){
    // |x|
    if (x<0) return -x;
    return x;
}

Heap inicializar_heap(){
    // CRIA UM HEAP VAZIO
    Heap novo;
    novo.passageiros = malloc(MAX_PASSAGEIROS*sizeof(p_passageiro));
    novo.n = 0;
    novo.max = MAX_PASSAGEIROS; 
    return novo;
}
typedef Heap *p_heap;

Passageiro *criar_passageiro(char *nome_atual,double avaliacao_atual,int x_passageiro,int y_passageiro,int x_destino,int y_destino){
    // CRIA UM PASSAGEIRO ATRAVES DE SEUS DADOS
    p_passageiro novo = malloc(sizeof(Passageiro));
    novo->nome = nome_atual;
    novo->avaliacao = avaliacao_atual;
    novo->x_passageiro = x_passageiro;
    novo->y_passageiro = y_passageiro;
    novo->x_destino = x_destino;
    novo->y_destino = y_destino;
    
    return novo;
}

void sobe_no_heap(p_heap heap,int n){
    // COMPARA SE O PAI TEM AVALIAÇÂO MENOR, SE TIVER, TROCA AMBOS E REPETE O PROCESSO COM O AVO
    if (n == 0){
        return;
    }
    if(heap->passageiros[(n+1)/2-1]->avaliacao < heap->passageiros[n]->avaliacao){
        p_passageiro aux = heap->passageiros[(n+1)/2-1];
        heap->passageiros[(n+1)/2-1] = heap->passageiros[n];
        heap->passageiros[n] = aux;
        sobe_no_heap(heap,(n+1)/2-1);
    }
}

void inserir(p_heap heap,p_passageiro passageiro_atual){
    // INSERE UM PASSAGEIRO NO HEAP
    heap->passageiros[heap->n] = passageiro_atual;
    sobe_no_heap(heap,heap->n);
    heap->n += 1;
}

int comparar_strings(char *str1,char *str2){
    // COMPARA SE DUAS STRINGS SAO IGUAIS
    int eh_igual = 1;
    int i;
    for (i = 0;str1[i] != '\0' && str2[i] != '\0';i++){
        if(str1[i] != str2[i]){
            eh_igual = 0;
        }
    }
    if(str1[i] != str2[i]){
        eh_igual = 0;
    }
    return eh_igual;
}

void consertar_heap(p_heap heap){
    // CONSERTA O HEAP, DEIXANDO O PAI SEMPRE COM AVALIAÇÂO MAIOR DO QUE SEUS FILHOS
    for (int i = heap->n-1;i>0;i--){
        if(heap->passageiros[(i+1)/2-1]->avaliacao < heap->passageiros[i]->avaliacao){

            p_passageiro aux = heap->passageiros[(i+1)/2-1];
            heap->passageiros[(i+1)/2-1] = heap->passageiros[i];
            heap->passageiros[i] = aux;
        }
    }
}

void remover(int i,p_heap heap){
    // REMOVE UM PASSAGEIRO i DO HEAP
    int n = heap->n;
    free(heap->passageiros[i]);
    for(int j = i;j<n-1;j++){
        heap->passageiros[j] = heap->passageiros[j+1];
    }
    heap->n -= 1;
}

void remover_por_nome(char *nome,p_heap heap){
    // REMOVE UM PASSAGEIRO A PARTIR DO NOME
    int i = 0;
    while(comparar_strings(nome,heap->passageiros[i]->nome) != 1){
        i++;
    }
    char *aux = heap->passageiros[i]->nome;

    remover(i,heap);
    consertar_heap(heap);
    free(aux);
}

void receber_passageiro(p_heap heap,int *x_atual,int *y_atual,double *rendimento_bruto,int *km_total){
    // "PASSAGEIRO ENTRA NO CARRO"
    // CALCULA GASTOS E GANHOS, REMOVE O PASSAGEIRO DO HEAP
    *km_total += modulo(heap->passageiros[0]->x_passageiro  -  *x_atual);
    *km_total += modulo(heap->passageiros[0]->y_passageiro  -  *y_atual);

    *rendimento_bruto += 1.4*modulo(heap->passageiros[0]->x_destino  -  heap->passageiros[0]->x_passageiro);
    *rendimento_bruto += 1.4*modulo(heap->passageiros[0]->y_destino  -  heap->passageiros[0]->y_passageiro);

    *km_total += modulo(heap->passageiros[0]->x_destino  -  heap->passageiros[0]->x_passageiro);
    *km_total += modulo(heap->passageiros[0]->y_destino  -  heap->passageiros[0]->y_passageiro);

    *x_atual = heap->passageiros[0]->x_destino;
    *y_atual = heap->passageiros[0]->y_destino;

    remover(0,heap);
    consertar_heap(heap);
}


int main(){

    p_passageiro passageiro_atual;
    char tipo_de_entrada, *nome_inserir,nome_excluir[15],*corrida_atual; // corrida_atual é o nome do passageiro atual
    double avaliacao_atual,rendimento_bruto= 0;
    int x_passageiro,y_passageiro,x_destino,y_destino;
    int x_atual = 0,y_atual = 0;
    int km_total= 0, uber_vazio = 1;
    Heap heap = inicializar_heap();

    scanf(" %c",&tipo_de_entrada);

    while(tipo_de_entrada !=  'T'){

        if (tipo_de_entrada == 'A'){
            nome_inserir=  malloc(sizeof(char)*MAX_NOME);
            scanf(" %s %lf %d %d %d %d",nome_inserir,&avaliacao_atual,&x_passageiro,&y_passageiro,&x_destino,&y_destino);
            passageiro_atual = criar_passageiro(nome_inserir,avaliacao_atual,x_passageiro,y_passageiro,x_destino,y_destino);
            inserir(&heap,passageiro_atual);
            printf("Cliente %s foi adicionado(a)\n",nome_inserir);
            if(uber_vazio == 1){
                corrida_atual = heap.passageiros[0]->nome;
                receber_passageiro(&heap,&x_atual,&y_atual,&rendimento_bruto,&km_total);
                uber_vazio = 0;
            }
        }
        if (tipo_de_entrada == 'C'){
            scanf(" %s",nome_excluir);
            rendimento_bruto += 7;
            printf("%s cancelou a corrida\n",nome_excluir);
            remover_por_nome(nome_excluir,&heap);
        }
        if (tipo_de_entrada == 'F'){
            printf("A corrida de %s foi finalizada\n",corrida_atual);
            free(corrida_atual);
            uber_vazio = 1;
            if (heap.n != 0){
                uber_vazio = 0;
                corrida_atual = heap.passageiros[0]->nome;
                receber_passageiro(&heap,&x_atual,&y_atual,&rendimento_bruto,&km_total);
            }
        }
        scanf(" %c",&tipo_de_entrada);
    }
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\nKm total: %d\nRendimento bruto: %.2lf\nDespesas: %.2lf\nRendimento liquido: %.2lf",km_total,rendimento_bruto,0.4104*km_total+57,3*rendimento_bruto/4-0.4104*km_total -57);
    free(heap.passageiros);
}