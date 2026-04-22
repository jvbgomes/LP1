#include <iostream>
using namespace std;

// x elevado a y;
int potencia(int x, int y) {
    if (y == 0) {
        return 1;
    }
    return x * potencia(x, y - 1);
}

int main() {
    int base, expoente;

    cout << "Coloque a base e o expoente: ";
    cin >> base >> expoente;

    cout <<  base << " elevado a " << expoente << " e "<< potencia(base, expoente) << endl;


    return 0;
}