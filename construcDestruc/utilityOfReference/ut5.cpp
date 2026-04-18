#include <iostream>
#include <string>
using namespace std;

void imprimirAluno(const Aluno& a) {
    cout << a.nome << " - " << a.matricula;
    // não pode modificar, não cria cópia
}

// Usado em loops que rodam muitas vezes
for (const Aluno& a : turma) {  // sem const& aqui copiaria cada aluno
    imprimirAluno(a);
}