#include <iostream>
#include <string>
using namespace std;

class ContaBancaria {
private:
    float saldo;

public:
    int numero;
    string titular;

    ContaBancaria() {
        cout << "Construindo conta bancaria sem informações!" << "\n";
        this->titular = "Sem titular";
        this->numero = 0;
        this->saldo = 0;
    }

    ContaBancaria(string titular, int numero) {
        cout << "Construindo conta bancaria!" << "\n";
        this->titular = titular;
        this->numero = numero;
        this->saldo = 0;
    }

    ContaBancaria(string titular, int numero, float saldo) {
        cout << "Construindo conta bancaria completa!" << "\n";
        this->titular = titular;
        this->numero = numero;
        this->saldo = saldo;
    }

    void ExibirConta() {
        cout << "Titular: " << this->titular << "\n";
        cout << "Numero: " << this->numero << "\n";
        cout << "Saldo: " << "R$" << this->saldo << "\n";
    }

};

int main () {
    ContaBancaria c1;
    ContaBancaria c2("Joao", 432321);
    ContaBancaria c3("Maria", 234956, 1235.65);

    c1.ExibirConta();
    c2.ExibirConta();
    c3.ExibirConta();

    return 0;
}