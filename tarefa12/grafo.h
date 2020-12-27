typedef struct Vertice{
    int valor;
    p_lista pais;
    p_lista filhos;
}Vertice;

typedef Vertice * p_vertice;

typedef struct Grafo{
    int largura;
    int total_termos;
    p_vertice vertices;
} Grafo;

typedef Grafo * p_grafo;


void adicionar_dependencia(p_grafo planilha,int posicao, int numero_do_vertice,int sinal);

Grafo inicializar_grafo(int total_de_termos,int largura);

void liberar_grafo(p_grafo grafo);

int eh_dependente(p_grafo planilha, int vertice1, int vertice2);