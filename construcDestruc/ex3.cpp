#include <iostream>
#include <string>
using namespace std;

class Conexao {
private:
    bool conectado;

public:
    string endereco;

    Conexao(string endereco) {
        cout << "Estabelecendo conexao com: " << endereco << "\n";
        this->endereco = endereco;
        this->conectado = true;
    }

    //usado pra garantir que o constructor acabe assim que sair do escopo.
    ~Conexao() {
        if (this->conectado == true) {
            cout << "Fechando conexao com: " << this->endereco << "\n";
        } else {
            cout << "Conexao com: " << this->endereco << " já estava fechada!\n";
        }
    }
    //utilizar o desconectar() junto com o destructor é uma boa pratica, pois você decide a hora que deve ser desconectado e ainda sim esta garantido que o destructor vai resolver caso algum erro ocorra.
    void desconectar() {
        if (this->conectado == true) {
            cout << "Desconectando de: " << this->endereco << "\n";
            this->conectado = false;
        }
    }
    
};

int main () {
    Conexao c1("www.google.com");
    Conexao c2("www.facebook.com");
    Conexao c3("www.twitter.com");

    c1.desconectar();
    c2.desconectar();
    c3.desconectar();
    
    // Ou pode ser feito assim:
    // desconectar() {
    //     c1.desconectar();
    //     c2.desconectar();
    //     c3.desconectar();
    // }

    return 0;
}