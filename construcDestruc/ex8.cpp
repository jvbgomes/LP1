#include <iostream>
using namespace std;

class Pilha {
private:
    int dados[100];
    int topo;

public:
    Pilha() {
        cout << "Pilha criada!\n";
        this->topo = -1;
    }

    ~Pilha() {
        cout << "Pilha destruida!\n";
    }

    void push(int valor) {
        if (topo >= 99) {
            cout << "Pilha cheia!\n";
            return;
        }
        dados[++topo] = valor;
        cout << valor << " adicionado a pilha.\n";
    }

    void pop() {
        if (topo < 0) {
            cout << "Pilha vazia!\n";
            return;
        }
        cout << dados[topo--] << " removido da pilha.\n";
    }

    void exibir() {
        if (topo < 0) {
            cout << "Pilha vazia!\n";
            return;
        }
        cout << "Pilha (topo -> base): ";
        for (int i = topo; i >= 0; i--) {
            cout << dados[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    Pilha p;
    p.push(10);
    p.push(20);
    p.push(30);
    p.exibir();
    p.pop();
    p.exibir();

    return 0;
}
