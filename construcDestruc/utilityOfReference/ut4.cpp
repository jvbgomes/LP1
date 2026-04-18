#include <iostream>
#include <string>
#include <vector>
using namespace std;

void lerNotas(vector<float>& notas) {
    float n;
    while (cin >> n) {
        notas.push_back(n);   // modifica o vector original
    }
}

int main() {
    vector<float> minhasNotas;
    lerNotas(minhasNotas);
    // minhasNotas agora está populado
}
