#include <stdio.h>
#include "professor_carlos.h"

Aluno receber_aluno(){
    Aluno aluno_atual;
    scanf(" %s",aluno_atual.nome);
    scanf(" %s",aluno_atual.sobrenome);
    scanf(" %d %d %d",&aluno_atual.nascimento.dia,&aluno_atual.nascimento.mes,&aluno_atual.nascimento.ano);
    return aluno_atual;
}

void receber_turmas(Turma t[50],int *qtd_turmas,int *k){
    int i,j,m;
    scanf(" %d %d",qtd_turmas,k);

    for (i = 0;i <*qtd_turmas;i++){
        scanf(" %d",&m);
        t[i].qtd = m;
        for (j = 0; j<m ; j++){
            t[i].alunos[j] = receber_aluno();
        }
    }
}

void executar_operacoes(Turma t[],int qtd_turmas,int k){
    Aluno A;
    int i,j,op;
    char padrao[15];

    for (i=0;i<k;i++){
        scanf("%d",&op);
        if (op == 1){
            scanf(" %d",&j);
            printf("%s\n",procura_novo_na_turma(t,qtd_turmas,j).nome);
        }
        if (op == 2){
            scanf(" %d",&j);
            printf("%s\n",procura_velho_na_turma(t,qtd_turmas,j).sobrenome);
        }
        if (op == 3){
            printf("%s\n",procura_velho_todas_turmas(t,qtd_turmas).nome);
        }
        if (op == 4){
            printf("%s\n",procura_novo_todas_turmas(t,qtd_turmas).sobrenome);
        }
        if (op == 5){
            scanf(" %s",padrao);
            printf("%d\n",conta_substrings(t,qtd_turmas,padrao));
        }
        if (op == 6){
            scanf(" %d",&j);
            A = receber_aluno();
            printf("%d\n",add_aluno(t,A,j));
        }
        
        if (op == 7){
            scanf(" %d",&j);
            printf("%d\n",remove_aluno(t,j));
        }
    }
}

int main(){
    int k,qtd_turmas;
    Turma t[50];

    receber_turmas(t,&qtd_turmas,&k);
    executar_operacoes(t,qtd_turmas,k);

    return 0;
}