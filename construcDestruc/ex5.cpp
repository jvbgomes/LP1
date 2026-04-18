#include <iostream>
#include <string>
using namespace std;

class Matematica {

    public: 

        int multiplicar(int a, int b) {
            cout << "Multiplicação de inteiros: " << endl;
            return a * b;
        }

        double multiplicar(double a, double b) {
            cout << "Multiplicação de doubles: " << endl;
            return a * b;
        }

        double multiplicar(int a, double b) {
            cout << "Multiplicação de inteiro e double: " << endl;
            return a * b;
        }

        int multiplicar(int a, int b, int c) {
            cout << "Multiplicação de três inteiros: " << endl;
            return a * b * c;
        }

};

int main () {

    Matematica m;

    cout << m.multiplicar(2, 3) << endl;
    cout << m.multiplicar(2.5, 3.5) << endl;
    cout << m.multiplicar(2, 3.5) << endl;
    cout << m.multiplicar(2, 3, 4) << endl;

    return 0;
}