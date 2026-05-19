#include <iostream>
#include <string>
using namespace std;

// Classe abstrata - nao pode ser instanciada diretamente
class Funcionario {
protected:
    string nome;
    string cpf;
    float salarioBase;

public:
    Funcionario(string nome, string cpf, float salarioBase)
        : nome(nome), cpf(cpf), salarioBase(salarioBase) {}

    virtual float calcularSalario() = 0;
    virtual string getCargo() = 0;

    void exibirInfo() {
        cout << "Nome: " << nome << endl;
        cout << "CPF: " << cpf << endl;
        cout << "Cargo: " << getCargo() << endl;
        cout << "Salario: R$ " << calcularSalario() << endl;
    }

    virtual ~Funcionario() {}
};

class Gerente : public Funcionario {
private:
    float bonus;
    int numSubordinados;

public:
    Gerente(string nome, string cpf, float salarioBase, float bonus, int numSub)
        : Funcionario(nome, cpf, salarioBase), bonus(bonus), numSubordinados(numSub) {}

    float calcularSalario() override {
        return salarioBase + bonus + (numSubordinados * 150.0);
    }

    string getCargo() override {
        return "Gerente";
    }
};

class Vendedor : public Funcionario {
private:
    float comissao;
    int vendasMes;

public:
    Vendedor(string nome, string cpf, float salarioBase, float comissao, int vendas)
        : Funcionario(nome, cpf, salarioBase), comissao(comissao), vendasMes(vendas) {}

    float calcularSalario() override {
        return salarioBase + (comissao * vendasMes);
    }

    string getCargo() override {
        return "Vendedor";
    }
};

class Estagiario : public Funcionario {
private:
    int horasTrabalhadas;
    float valorHora;

public:
    Estagiario(string nome, string cpf, float valorHora, int horas)
        : Funcionario(nome, cpf, 0), valorHora(valorHora), horasTrabalhadas(horas) {}

    float calcularSalario() override {
        return valorHora * horasTrabalhadas;
    }

    string getCargo() override {
        return "Estagiario";
    }
};

int main() {
    Gerente g("Carlos", "111.222.333-44", 5000.0, 1000.0, 8);
    Vendedor v("Ana", "555.666.777-88", 1800.0, 50.0, 30);
    Estagiario e("Pedro", "999.888.777-66", 25.0, 120);

    cout << "=== Folha de Pagamento ===" << endl << endl;

    g.exibirInfo();
    cout << endl;

    v.exibirInfo();
    cout << endl;

    e.exibirInfo();

    return 0;
}
