#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    string nome;
    int idade;

    Animal(string nome, int idade) : nome(nome), idade(idade) {}

    void comer() {
        cout << nome << " esta comendo." << endl;
    }

    void dormir() {
        cout << nome << " esta dormindo." << endl;
    }

    void exibirInfo() {
        cout << "Animal: " << nome << ", Idade: " << idade << " anos" << endl;
    }
};

class Cachorro : public Animal {
public:
    string raca;

    Cachorro(string nome, int idade, string raca)
        : Animal(nome, idade), raca(raca) {}

    void latir() {
        cout << nome << " faz: Au au!" << endl;
    }

    void exibirInfo() {
        Animal::exibirInfo();
        cout << "Raca: " << raca << endl;
    }
};

class Gato : public Animal {
public:
    bool domestico;

    Gato(string nome, int idade, bool domestico)
        : Animal(nome, idade), domestico(domestico) {}

    void miar() {
        cout << nome << " faz: Miau!" << endl;
    }

    void exibirInfo() {
        Animal::exibirInfo();
        cout << "Domestico: " << (domestico ? "Sim" : "Nao") << endl;
    }
};

int main() {
    Cachorro dog("Rex", 3, "Labrador");
    Gato cat("Mimi", 5, true);

    dog.exibirInfo();
    dog.latir();
    dog.comer();

    cout << endl;

    cat.exibirInfo();
    cat.miar();
    cat.dormir();

    return 0;
}
