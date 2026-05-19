#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Forma {
protected:
    string cor;

public:
    Forma(string cor) : cor(cor) {}

    virtual float calcularArea() = 0;
    virtual float calcularPerimetro() = 0;

    virtual void exibirInfo() {
        cout << "Cor: " << cor << endl;
        cout << "Area: " << calcularArea() << endl;
        cout << "Perimetro: " << calcularPerimetro() << endl;
    }

    virtual ~Forma() {}
};

class Circulo : public Forma {
private:
    float raio;
    const float PI = 3.14159;

public:
    Circulo(string cor, float raio) : Forma(cor), raio(raio) {}

    float calcularArea() override {
        return PI * raio * raio;
    }

    float calcularPerimetro() override {
        return 2 * PI * raio;
    }

    void exibirInfo() override {
        cout << "=== Circulo ===" << endl;
        cout << "Raio: " << raio << endl;
        Forma::exibirInfo();
    }
};

class Retangulo : public Forma {
private:
    float largura;
    float altura;

public:
    Retangulo(string cor, float largura, float altura)
        : Forma(cor), largura(largura), altura(altura) {}

    float calcularArea() override {
        return largura * altura;
    }

    float calcularPerimetro() override {
        return 2 * (largura + altura);
    }

    void exibirInfo() override {
        cout << "=== Retangulo ===" << endl;
        cout << "Largura: " << largura << " | Altura: " << altura << endl;
        Forma::exibirInfo();
    }
};

class Triangulo : public Forma {
private:
    float base;
    float altura;
    float lado1, lado2;

public:
    Triangulo(string cor, float base, float altura, float lado1, float lado2)
        : Forma(cor), base(base), altura(altura), lado1(lado1), lado2(lado2) {}

    float calcularArea() override {
        return (base * altura) / 2;
    }

    float calcularPerimetro() override {
        return base + lado1 + lado2;
    }

    void exibirInfo() override {
        cout << "=== Triangulo ===" << endl;
        cout << "Base: " << base << " | Altura: " << altura << endl;
        Forma::exibirInfo();
    }
};

int main() {
    vector<Forma*> formas;
    formas.push_back(new Circulo("Azul", 5.0));
    formas.push_back(new Retangulo("Vermelho", 4.0, 6.0));
    formas.push_back(new Triangulo("Verde", 3.0, 4.0, 4.0, 5.0));

    for (Forma* f : formas) {
        f->exibirInfo();
        cout << endl;
    }

    for (Forma* f : formas) {
        delete f;
    }

    return 0;
}
