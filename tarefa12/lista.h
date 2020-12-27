

typedef struct Lista{
    int vertice;
    int dependencia;
    struct Lista * prox;
}Lista;

typedef struct Lista *p_lista;

p_lista inserir_na_lista(p_lista lista,int elemento, int sinal);