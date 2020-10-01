typedef struct tinta{
    /*pctg_cor é a porcentagem de uma determinada cor primaria
      colorida_branca_ou_preta armazena 0 para colorida,1 para branca e 2 para preta   */
    int colorida_branca_ou_preta;
    double pctg_amrl;
    double pctg_verm;
    double pctg_azul;
}Tinta;

Tinta inicializar_tinta(double,double,double);

Tinta misturar_tintas(Tinta,Tinta,double,double);