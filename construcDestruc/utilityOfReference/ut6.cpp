#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapMinMax(int arr[], int n) {
    int minIdx = 0, maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) minIdx = i;
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }
    swap(arr[minIdx], arr[maxIdx]);
}

int main() {
    int a = 5, b = 10;
    cout << "Antes: a = " << a << ", b = " << b << "\n";
    swap(a, b);
    cout << "Depois: a = " << a << ", b = " << b << "\n";

    int arr[] = {3, 1, 7, 2, 9, 4};
    int n = 6;

    cout << "\nArray original: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";

    swapMinMax(arr, n);

    cout << "\nApos trocar min e max: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
