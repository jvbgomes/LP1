#include <iostream>
#include <string>
using namespace std;

class Troca {
public:
    void trocarPorValor(int a, int b) {
        a = a + 10;
        b = b + 5;
        cout << "\nTroca dentro da função (valor): " << "x = " << a << ", y = " << b << endl;
    }

    void trocarPorReferencia(int &a, int &b) {
        a = a + 10;
        b = b + 5;
        cout << "\nTroca dentro da função (referência): " << "x = " << a << ", y = " << b << endl;
    }
};

int main() {
    Troca t;
    int x = 5, y = 10;

    cout << "Antes da troca por valor: x = " << x << ", y = " << y << endl;
    t.trocarPorValor(x, y);
    cout << "\nDepois da troca por valor: x = " << x << ", y = " << y << endl;

    x = 5, y = 10;
    cout << "\nAntes da troca por referência: x = " << x << ", y = " << y << endl;
    t.trocarPorReferencia(x, y);
    cout << "\nDepois da troca por referência: x = " << x << ", y = " << y << endl;

    return 0;
}