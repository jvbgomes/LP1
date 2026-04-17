#include <stdio.h>

#define MAX_ALUNOS 50

struct Data {
    int dia;
    int mes;
    int ano;
};

// Em C, a acao fica em uma funcao separada da struct
void imprimirData(struct Data d) {
    printf("%d/%d/%d", d.dia, d.mes, d.ano);
}

struct Aluno {
    int matricula;
    char nome[50];
    struct Data nascimento;
};

void imprimirAluno(struct Aluno a) {
    printf("Matricula: %d | Nome: %s | Nasc: ", a.matricula, a.nome);
    imprimirData(a.nascimento);
    printf("\n");
}

int main() {
    struct Aluno turma[MAX_ALUNOS];
    int totalAlunos = 0;
    int opcao = -1;

    printf("=== Sistema de Gestao Escolar ===\n");

    while (opcao != 0) {
        printf("\nMenu:\n");
        printf("1. Adicionar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (totalAlunos < MAX_ALUNOS) {
                printf("Digite a matricula: ");
                scanf("%d", &turma[totalAlunos].matricula);

                printf("Digite o primeiro nome do aluno: ");
                scanf("%49s", turma[totalAlunos].nome);

                printf("Data de nascimento (Dia): ");
                scanf("%d", &turma[totalAlunos].nascimento.dia);
                printf("Data de nascimento (Mes): ");
                scanf("%d", &turma[totalAlunos].nascimento.mes);
                printf("Data de nascimento (Ano): ");
                scanf("%d", &turma[totalAlunos].nascimento.ano);

                totalAlunos++;
                printf("Aluno adicionado com sucesso!\n");
            } else {
                printf("Capacidade maxima da turma atingida!\n");
            }
        } else if (opcao == 2) {
            printf("\n--- Lista de Alunos ---\n");
            for (int i = 0; i < totalAlunos; i++) {
                imprimirAluno(turma[i]);
            }
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}