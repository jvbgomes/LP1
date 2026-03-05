#include <stdio.h>

int main() {
    int num, factorial;
    printf("Digite um numero: ");
    scanf("%d", &num);

    factorial = 1;
    for(int i = 1; i <= num; i++) {
        factorial *= i;
    }
    printf(" %d! = %d", num, factorial);
    return 0;
}