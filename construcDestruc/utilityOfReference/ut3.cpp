#include <iostream>
using namespace std;

// Funções que trocam de valores(swap), enfatizando a importancia de passar por reference(&).

void trocar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5, y = 10;
    trocar(x, y);
    cout << x << " " << y;  // 10 5

    return 0;
}