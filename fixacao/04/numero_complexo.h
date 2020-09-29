typedef struct complexo{
    double parte_real;
    double parte_imag;
}Complexo;

Complexo inicializar_numero(double real,double imag);

void imprimir_numero(Complexo num);

Complexo op(Complexo num1,char operacao, Complexo num2);

int comp(Complexo num1,char comparacao, Complexo num2);

Complexo obter_conjugado(Complexo num);