#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string nome;
    int idade;

public:
    Animal(string nome, int idade) {
        cout << "Animal criado: " << nome << "\n";
        this->nome = nome;
        this->idade = idade;
    }

    virtual ~Animal() {
        cout << "Animal " << nome << " destruido.\n";
    }

    virtual void fazerSom() {
        cout << nome << " faz um som generico.\n";
    }

    void exibir() {
        cout << "Nome: " << nome << ", Idade: " << idade << " anos\n";
    }
};

class Cachorro : public Animal {
public:
    Cachorro(string nome, int idade) : Animal(nome, idade) {}

    void fazerSom() override {
        cout << nome << " diz: Au au!\n";
    }
};

class Gato : public Animal {
public:
    Gato(string nome, int idade) : Animal(nome, idade) {}

    void fazerSom() override {
        cout << nome << " diz: Miau!\n";
    }
};

int main() {
    Animal* animais[3];
    animais[0] = new Cachorro("Rex", 3);
    animais[1] = new Gato("Mingau", 2);
    animais[2] = new Cachorro("Bolt", 5);

    for (int i = 0; i < 3; i++) {
        animais[i]->exibir();
        animais[i]->fazerSom();
        cout << "\n";
    }

    for (int i = 0; i < 3; i++) {
        delete animais[i];
    }

    return 0;
}
