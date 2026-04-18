#include <iostream>
#include <string>
using namespace std;
class Turma {
    Aluno alunos[500];
    string nomeProfessor;
    // ... muitos atributos
};

// RUIM — copia os 500 alunos a cada chamada
void adicionarAluno(Turma t, Aluno novo) {  // cópia cara!
    // ...
}

// BOM — trabalha direto na turma original
void adicionarAluno(Turma& t, Aluno novo) {
    // ...
}