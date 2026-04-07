#include <iostream>
#include <string>
using namespace std;

class Pessoa {
public:
    int idade;
    int vida;
    
    void pessoa_mostrar() {
        cout << "Idade: " << this->idade << " | Vida: " << this->vida << "\n";
    }
    
    void init() {
       this->idade = 20;
       this->vida = 100;
    }
};

//this é um ponteiro implícito para o objeto atual, ou seja, ele aponta para a instância da classe que está chamando o método. Ele é usado para acessar os membros da classe dentro dos métodos. No exemplo acima, usamos this->idade e this->vida para acessar os atributos idade e vida do objeto atual.
#define TAM 1000000

int main() {


    Pessoa *galera[TAM]= new Pessoa[TAM];    // Pessoa *galer[TAM] = (Pessoa *)malloc(TAM * sizeof(Pessoa));

    for (int i = 0; i < TAM; i++) {
        galera[i]->init();
    }

    Pessoa joao;
    joao.init();

    Pessoa maria;
    maria.init();

    joao.pessoa_mostrar();
    maria.pessoa_mostrar();

    //free(galera); 
    //Uma boa pratica, mas no main não seria tão necessário, pois o main ja libera a memória automaticamente.
    delete [] galera;

    cout << "Pressione zero para finalizar: ";
    int input;
    cin >> input;


    return 0;
}