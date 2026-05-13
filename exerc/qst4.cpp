#include <iostream>
using namespace std;

int buscaBinaria(int arr[], int n, int alvo) {
    int esquerda = 0, direita = n - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (arr[meio] == alvo) return meio;
        if (arr[meio] < alvo) esquerda = meio + 1;
        else direita = meio - 1;
    }

    return -1;
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 42, 55, 72};
    int n = 10;
    int alvo;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    cout << "Digite o numero a buscar: ";
    cin >> alvo;

    int idx = buscaBinaria(arr, n, alvo);

    if (idx != -1) {
        cout << alvo << " encontrado na posicao " << idx << ".\n";
    } else {
        cout << alvo << " nao encontrado.\n";
    }

    return 0;
}
