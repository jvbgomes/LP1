#include <iostream>
#include <cmath>
using namespace std;

class Circulo {
private:
    float raio;
    static const float PI;

public:
    Circulo(float raio) {
        cout << "Circulo criado com raio " << raio << ".\n";
        this->raio = raio;
    }

    ~Circulo() {
        cout << "Circulo com raio " << raio << " destruido.\n";
    }

    float area() {
        return PI * raio * raio;
    }

    float perimetro() {
        return 2 * PI * raio;
    }

    void exibir() {
        cout << "Raio: " << raio << "\n";
        cout << "Area: " << area() << "\n";
        cout << "Perimetro: " << perimetro() << "\n";
    }
};

const float Circulo::PI = 3.14159f;

int main() {
    Circulo c1(5.0f);
    Circulo c2(10.0f);

    c1.exibir();
    c2.exibir();

    return 0;
}
