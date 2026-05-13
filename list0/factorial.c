#include <stdio.h>

int factorial(int n) {
    if (n < 0) return -1;
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int num;
    printf("Digite um numero: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Fatorial nao definido para numeros negativos.\n");
        return 1;
    }

    printf("%d! = %d\n", num, factorial(num));
    return 0;
}