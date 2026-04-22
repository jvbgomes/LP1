#include <iostream>
#include <string>
using namespace std;

class ContaBancaria
{
private:
    float saldo;

public:
    string nome;
    string cpf;
    int numConta;

    static int qtdContas;

    ContaBancaria() : nome("Usuario"), cpf(""), numConta(0), saldo(0.0) {
        cout << "Cadastrando usuario no sistema do Banco:\n";
        qtdContas++;
    }

    ContaBancaria(string nome, string cpf, int numConta) : nome(nome), cpf(cpf), numConta(numConta), saldo(0.0) {
        cout << "Cadastrando usuario com nome, cpf e numero:\n";
        qtdContas++;
    }

    ContaBancaria(string nome, string cpf, int numConta, float saldo) : nome(nome), cpf(cpf), numConta(numConta), saldo(saldo) {
        cout << "Cadastrando usuario completo:\n\n";
        qtdContas++;
    }

    ~ContaBancaria() {
        cout << "Apagando conta do sistema bancario:\n"
             << "Cliente: " << this->nome << " foi retirado do sistema bancario." << endl;
        qtdContas--;
    }

    float depositar(float valor) {
        if (valor <= 0) {
            cout << "Valor de depósito inválido. O valor deve ser positivo." << endl;
            return this->saldo;
        }
        this->saldo += valor;
        return this->saldo;
    }

    float sacar(float valor) {
        if (valor <= 0) {
            cout << "Valor de saque inválido. O valor deve ser positivo." << endl;
            return this->saldo;
        } else if (valor > this->saldo) {
            cout << "Saldo insuficiente para realizar o saque." << endl;
            return this->saldo;
        }
        this->saldo -= valor;
        return this->saldo;
    }

    float transferir(float qtd, ContaBancaria& destinatario) {
        if (qtd <= 0) {
            cout << "Valor de transferência inválida. O valor deve ser positivo." << endl;
            return this->saldo;
        }
        if (this->saldo < qtd) {
            cout << "Saldo insuficiente para realizar a transferência." << endl;
            return this->saldo;
        }
        this->saldo -= qtd;
        destinatario.depositar(qtd);
        return this->saldo;
    }

    float getSaldo() const {
        return this->saldo;
    }

    void exibirInfo() const {
        cout << "=== Conta " << this->numConta << " ===\n";
        cout << "Titular: " << this->nome << "\n";
        cout << "CPF: " << this->cpf << "\n";
        cout << "Saldo: R$ " << this->saldo << "\n";
    }

    static int qtdContasCadastradas() {
        return qtdContas;
    }
};
int ContaBancaria::qtdContas = 0;

int main() {

    ContaBancaria c1("Joao", "111.222.333-44", 1001, 1000.0);
    ContaBancaria c2("Maria", "555.666.777-88", 1002, 500.0);
    
    c1.exibirInfo();
    c2.exibirInfo();
    
    cout << "\n--- Operacoes ---\n";
    c1.depositar(200);
    c1.transferir(300, c2);
    c2.sacar(100);
    
    cout << "\n--- Estado final ---\n";
    c1.exibirInfo();
    c2.exibirInfo();
    
    cout << "\nTotal de contas: " << ContaBancaria::qtdContasCadastradas() << "\n";

    return 0;
}