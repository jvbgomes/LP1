#include <iostream>
#include <string>
using namespace std;

class Veiculo {
protected:
    string marca;
    int ano;
    float velocidadeMax;

public:
    Veiculo(string marca, int ano, float velocidadeMax)
        : marca(marca), ano(ano), velocidadeMax(velocidadeMax) {}

    void ligar() {
        cout << marca << " ligado." << endl;
    }

    void desligar() {
        cout << marca << " desligado." << endl;
    }

    void exibirInfo() {
        cout << "Marca: " << marca << " | Ano: " << ano
             << " | Vel. Max: " << velocidadeMax << " km/h" << endl;
    }
};

class Carro : public Veiculo {
private:
    int numPortas;

public:
    Carro(string marca, int ano, float velocidadeMax, int numPortas)
        : Veiculo(marca, ano, velocidadeMax), numPortas(numPortas) {}

    void abrirPorta(int num) {
        if (num < 1 || num > numPortas) {
            cout << "Porta invalida." << endl;
            return;
        }
        cout << "Porta " << num << " aberta." << endl;
    }

    void exibirInfo() {
        Veiculo::exibirInfo();
        cout << "Portas: " << numPortas << endl;
    }
};

class CarroEsportivo : public Carro {
private:
    bool turbo;
    float aceleracao;

public:
    CarroEsportivo(string marca, int ano, float velMax, bool turbo, float aceleracao)
        : Carro(marca, ano, velMax, 2), turbo(turbo), aceleracao(aceleracao) {}

    void ativarTurbo() {
        if (turbo) {
            cout << marca << " - TURBO ATIVADO!" << endl;
        } else {
            cout << marca << " nao tem turbo." << endl;
        }
    }

    void exibirInfo() {
        Carro::exibirInfo();
        cout << "Turbo: " << (turbo ? "Sim" : "Nao")
             << " | Aceleracao 0-100: " << aceleracao << "s" << endl;
    }
};

int main() {
    Veiculo v("Generico", 2020, 120.0);
    Carro c("Honda Civic", 2023, 210.0, 4);
    CarroEsportivo cs("Ferrari", 2024, 320.0, true, 3.1);

    cout << "=== Veiculo ===" << endl;
    v.exibirInfo();
    v.ligar();

    cout << "\n=== Carro ===" << endl;
    c.exibirInfo();
    c.abrirPorta(2);

    cout << "\n=== Carro Esportivo ===" << endl;
    cs.exibirInfo();
    cs.ativarTurbo();

    return 0;
}
