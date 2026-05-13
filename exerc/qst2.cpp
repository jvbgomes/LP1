#include <iostream>
using namespace std;

void multiplicarMatrizes(int a[2][2], int b[2][2], int resultado[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                resultado[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void exibirMatriz(int m[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int resultado[2][2];

    cout << "Matriz A:\n";
    exibirMatriz(a);

    cout << "Matriz B:\n";
    exibirMatriz(b);

    multiplicarMatrizes(a, b, resultado);

    cout << "A x B:\n";
    exibirMatriz(resultado);

    return 0;
}
