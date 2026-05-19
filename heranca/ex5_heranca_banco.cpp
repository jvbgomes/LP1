#include <iostream>
#include <string>
using namespace std;

class Conta {
protected:
    string titular;
    string agencia;
    int numero;
    float saldo;

public:
    Conta(string titular, string agencia, int numero, float saldoInicial = 0)
        : titular(titular), agencia(agencia), numero(numero), saldo(saldoInicial) {}

    virtual void depositar(float valor) {
        if (valor <= 0) {
            cout << "Valor invalido." << endl;
            return;
        }
        saldo += valor;
        cout << "Deposito de R$ " << valor << " realizado." << endl;
    }

    virtual bool sacar(float valor) {
        if (valor <= 0 || valor > saldo) {
            cout << "Saque nao permitido." << endl;
            return false;
        }
        saldo -= valor;
        cout << "Saque de R$ " << valor << " realizado." << endl;
        return true;
    }

    virtual void exibirInfo() {
        cout << "Titular: " << titular << endl;
        cout << "Agencia: " << agencia << " | Conta: " << numero << endl;
        cout << "Saldo: R$ " << saldo << endl;
    }

    float getSaldo() { return saldo; }

    virtual ~Conta() {}
};

class ContaCorrente : public Conta {
private:
    float limite;
    float taxaMensal;

public:
    ContaCorrente(string titular, string agencia, int numero, float saldo, float limite, float taxa)
        : Conta(titular, agencia, numero, saldo), limite(limite), taxaMensal(taxa) {}

    bool sacar(float valor) override {
        if (valor <= 0) {
            cout << "Valor invalido." << endl;
            return false;
        }
        if (valor > saldo + limite) {
            cout << "Limite excedido." << endl;
            return false;
        }
        saldo -= valor;
        cout << "Saque de R$ " << valor << " realizado (pode usar limite)." << endl;
        return true;
    }

    void cobrarTaxa() {
        saldo -= taxaMensal;
        cout << "Taxa mensal de R$ " << taxaMensal << " cobrada." << endl;
    }

    void exibirInfo() override {
        cout << "=== Conta Corrente ===" << endl;
        Conta::exibirInfo();
        cout << "Limite: R$ " << limite << " | Taxa: R$ " << taxaMensal << "/mes" << endl;
    }
};

class ContaPoupanca : public Conta {
private:
    float rendimentoMensal;

public:
    ContaPoupanca(string titular, string agencia, int numero, float saldo, float rendimento)
        : Conta(titular, agencia, numero, saldo), rendimentoMensal(rendimento) {}

    void aplicarRendimento() {
        float rendimento = saldo * rendimentoMensal;
        saldo += rendimento;
        cout << "Rendimento de R$ " << rendimento << " aplicado." << endl;
    }

    void exibirInfo() override {
        cout << "=== Conta Poupanca ===" << endl;
        Conta::exibirInfo();
        cout << "Rendimento: " << rendimentoMensal * 100 << "% ao mes" << endl;
    }
};

int main() {
    ContaCorrente cc("Joao Silva", "0001", 12345, 1000.0, 500.0, 30.0);
    ContaPoupanca cp("Maria Souza", "0001", 67890, 2000.0, 0.005);

    cc.exibirInfo();
    cout << endl;
    cc.depositar(300.0);
    cc.sacar(1400.0);
    cc.cobrarTaxa();
    cout << endl;

    cp.exibirInfo();
    cout << endl;
    cp.depositar(500.0);
    cp.aplicarRendimento();

    return 0;
}
