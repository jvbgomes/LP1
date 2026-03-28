#include <iostream>
#include <string>
using namespace std;

#define MAX_ALUNOS 50

class Data {
public: 
    int dia;
    int mes;
    int ano;

    void imprimirData() {
        cout << dia << mes << ano << "\n";
    }    
};

class Aluno {
public:    
    int matricula;
    string nome;
    class Data nascimento;

    void imprimirAluno() {
        cout << "Matricula: " << matricula << " | Nome: " << nome << " | Nasc: " ;
        nascimento.imprimirData();
        cout << "\n";
    }
};

int main() {
    Aluno turma[MAX_ALUNOS];
    int totalAlunos = 0;
    int opcao = -1;

    cout << "=== Sistema de Gestao Escolar ===" << "\n" ;

    while (opcao != 0) {
        cout << "\n" << "Menu" << "\n" ;
        cout << "1. Adicionar Aluno" << "\n" ;
        cout << "2. Listar Alunos" << "\n" ;
        cout << "0. Sair" << "\n" ;
        cout << "Escolha: " ;
        cin >> opcao;

        if (opcao == 1) {
            if (totalAlunos < MAX_ALUNOS) {
                cout << "Digite a matricula: " ;
                cin >> turma[totalAlunos].matricula;

                cout << "Digite o primeiro nome do aluno: " ;
                cin >> turma[totalAlunos].nome;

                cout << "Data de nascimento(dia): " ;
                cin >> turma[totalAlunos].nascimento.dia;

                cout << "Data de nascimento(mes): " ;
                cin >> turma[totalAlunos].nascimento.mes;

                cout << "Data de nascimento(ano): " ;
                cin >> turma[totalAlunos].nascimento.ano;

                totalAlunos++;
                cout << "Aluno adicionado com sucesso!" << "\n" ;
            } else {
                cout << "Capacidade maxima da turma foi atingida!" << "\n" ;
            }

        } else if (opcao == 2) {
            cout << "\n" << "--- Lista de Alunos ---" << "\n" ;
            for (int i = 0; i < totalAlunos; i++) {
                turma[i].imprimirAluno();
            }
        } else if (opcao != 0) {
            cout << "Opcao invalida" << "\n" ;
        }
    }

    return 0;
}
