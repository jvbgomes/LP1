#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;

    No(int v) : valor(v), proximo(nullptr) {}
};

class ListaEncadeada {
private:
    No* cabeca;

public:
    ListaEncadeada() : cabeca(nullptr) {
        cout << "Lista criada!\n";
    }

    ~ListaEncadeada() {
        No* atual = cabeca;
        while (atual != nullptr) {
            No* prox = atual->proximo;
            delete atual;
            atual = prox;
        }
        cout << "Lista destruida!\n";
    }

    void inserir(int valor) {
        No* novo = new No(valor);
        novo->proximo = cabeca;
        cabeca = novo;
    }

    void exibir() {
        No* atual = cabeca;
        cout << "Lista: ";
        while (atual != nullptr) {
            cout << atual->valor << " -> ";
            atual = atual->proximo;
        }
        cout << "null\n";
    }

    void remover(int valor) {
        No* atual = cabeca;
        No* anterior = nullptr;

        while (atual != nullptr && atual->valor != valor) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual == nullptr) {
            cout << valor << " nao encontrado.\n";
            return;
        }

        if (anterior == nullptr) {
            cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }

        delete atual;
        cout << valor << " removido.\n";
    }
};

int main() {
    ListaEncadeada lista;
    lista.inserir(10);
    lista.inserir(20);
    lista.inserir(30);
    lista.exibir();
    lista.remover(20);
    lista.exibir();

    return 0;
}
