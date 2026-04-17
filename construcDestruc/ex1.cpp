#include <iostream>
using namespace std;

class Retangulo {
public:
    float largura;
    float altura;

    Retangulo(float largura, float altura) {
        cout << "Construindo retangulo: " << largura << " x "<< altura << endl;
        this->largura = largura;
        this->altura = altura;
    }

    float calcularArea() {
        return this->largura * this->altura;
    }

    void exibirArea() {
        cout << "Area do retangulo: " << this->calcularArea() << endl;
    }

};

int main () {

    Retangulo r1(12.5, 20.7);
    Retangulo r2(5.2, 10.0);
    Retangulo r3(3.0, 4.0);
    
    r1.exibirArea();
    r2.exibirArea();
    r3.exibirArea();

    return 0;
}