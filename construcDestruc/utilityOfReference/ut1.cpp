#include <iostream>
using namespace std;

// Como fazer uma função que divide e retorna quociente E resto?
void dividir(int a, int b, int& quociente, int& resto) {
    quociente = a / b;
    resto     = a % b;
}

int main() {
    int q, r;
    dividir(17, 5, q, r);
    cout << "17 / 5 = " << q << " resto " << r;  // 3 resto 2
}