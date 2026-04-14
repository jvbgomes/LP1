#include <iostream>
#include <string>
using namespace std;

class Conta {
public:
    int conta = 0;
}

class Cliente {
private:
    float saldo;
    Conta *conta;
public: 
    string nome;

    Cliente() {
        cout << "Construindo cliente sem nome! " << endl;
        this->saldo = 0;
        this->nome = "Sem nome";
        this->contas = 0;
    }

    Cliente(string nome) {
        cout << "Construindo cliente! " << endl;
        this->saldo = 0;
        this->nome = nome;
        this->contas = 0;
    }

    void abrirConta(int quantas) {
        this->contas = new Conta[quantas];
    }

    void depositar(float valor) {
        if (this->saldo <= 0) {
            cout << "Só é permitido depositos positivos!" << endl;
            return;
        }    
        this->saldo += valor;
    }

    void transferir(float quanto, Cliente *para_quem) {
        //quanto nao pode ser negativo
        if (quanto <= 0) {
            cout << "Só é permitido transferencias positivas!" << endl;
            return;
        }

        if (this->saldo >= quanto) {
            this->saldo -= quanto;
            para_quem->depositar(quanto);
        } else {
            cout <<"Saldo insuficiente!" << endl;
        }
    }

    ~Cliente() {
        cout << "Fechar conta no banco central" << endl;
        if (this->contas != 0) {
            delete this->contas;
            this->contas = 0;
        }
    }
};

int main() {
    Cliente ori("Oriosvaldo");
    Cliente joa("Joaquina");
    Cliente mari;

//depósito
    ori.depositar(1000);

// transferir 500 de ori para joa
    ori.transferir(500, &joa);

// trnasferir 600 de ori para mari    
    ori.transferir(600, &mari);

    return 0;
}