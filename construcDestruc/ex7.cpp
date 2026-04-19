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
        cout << "Cadastrando usuário no sistema do Banco:\n";
        qtdContas++;
    }

    ContaBancaria(string nome, string cpf, int numConta) : nome(nome), cpf(cpf), numConta(numConta), saldo(0.0) {
        cout << "Cadastrando usuário com nome, cpf e numero:\n";
        qtdContas++;
    }

    ContaBancaria(string nome, string cpf, int numConta, float saldo) : nome(nome), cpf(cpf), numConta(numConta), saldo(saldo) {
        cout << "Cadastrando usuário completo:\n";
        qtdContas++;
    }

    ~ContaBancaria() {
        cout << "Apagando conta do sistema bancario:\n"
             << "Cliente:" << this->nome << "foi retirado do sistema bancario." << endl;
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

    static int qtdContasCadastradas() {
        return qtdContas;
    }
};
int ContaBancaria::qtdContas = 0;

int main() {

    return 0;
}