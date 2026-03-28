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
        cout << "Matrícula: " << matricula << " | Nome: " << nome << " | Nasc: " << ;
        imprimirData(nascimento);
        cout << "\n";
    }
}
