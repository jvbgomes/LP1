#include <iostream>
#include <string>
using namespace std;

class Funcionario {
private:    
    float salario;
public:
    string nome;
    int idade;

    static int contaFunc;

    Funcionario() {
        cout << "Cadastrando funcionario sem informações...\n";
        this->nome = "Funcionario";
        this->idade = 0;
        this->salario = 0.0;
        contaFunc++;
    }

    Funcionario(string nome, float salario) {
        cout << "Cadastrando funcionario completo:\n";
        this->nome = nome;
        this->salario = salario;
        this->idade = 0;
        contaFunc++;
    }

    Funcionario(string nome, int idade, float salario) {
        cout << "Cadastro com todas as informações:\n";
        this->nome = nome;
        this->idade = idade;
        this->salario = salario;
        contaFunc++;
    }

    ~Funcionario() {
        cout << "Funcionario " << this->nome << " foi removido do sistema.\n";
        contaFunc--;
    }

    static void deletaGrupoDeFuncionarios(Funcionario* funcionarios, int tamanho) {
        for (int i = 0; i < tamanho; i++) {
            if (funcionarios[i].nome == "Funcionario") {
                cout << "Funcionario sem nome, não pode ser deletado!\n";
                continue;
            } else {
                cout << "Deletando funcionario: " << funcionarios[i].nome << "\n";
            }
        }
    }
    // 
    static void MostrarTotalFunc() {
        cout << "Total de funcionarios cadastrados: " << Funcionario::contaFunc << endl;
    }

};
//deve ser inicializada fora da classe, pois é uma var estatica, pertence a classe mas nao a um obj especifico.
int Funcionario::contaFunc = 0;

int main () {
    cout << "Iniciando cadastro de funcionarios...\n\n";
    
    Funcionario *funcionario[10];
    funcionario[0] = new Funcionario();
    funcionario[1] = new Funcionario("João", 2000.0);
    funcionario[2] = new Funcionario("Maria", 3000.0);
    funcionario[3] = new Funcionario("Pedro", 25, 2500.0);
    funcionario[4] = new Funcionario("Ana", 30, 3500.0);
    funcionario[5] = new Funcionario("Lucas", 28, 2800.0);
    funcionario[6] = new Funcionario("Carla", 32, 4000.0);
    funcionario[7] = new Funcionario("Rafael", 27, 2700.0);
    funcionario[8] = new Funcionario("Beatríz", 29, 3200.0); 
    funcionario[9] = new Funcionario("Nicollas", 20, 4600.0);
    
    cout << "\n\nAferindo o total de funcionarios cadastrados...\n\n";

    // :: é o operador de resolução de escopo, usa-se em membros estáticos para acessar a variável ou método sem precisar de um objeto específico.
    Funcionario::MostrarTotalFunc(); // Acessando o método estático para mostrar o total de funcionários cadastrados.
    
    cout << "Iniciando processo de exclusão de funcionarios...\n\n";

    for (int i = 0; i < 10; i++) {
        if (funcionario[i]->nome == "Funcionario") {
            cout << "Funcionario sem nome, não pode ser deletado!\n";
        } else {
            cout << "Deletando funcionario: " << funcionario[i]->nome << "\n";
        }
        //deleta todos os funcionarios
        delete funcionario[i];
        funcionario[i] = nullptr; // Evita dangling pointer
    }


    return 0;
}