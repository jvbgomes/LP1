#include <stdio.h>

int main() {
    int n;
    int primo = 1;

    scanf("%d", &n);

    if (n <= 1) {
        primo = 0;
    } else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                primo = 0;
                break;
            }
        }
    }

    if (primo) {
        printf("%d eh primo\n", n);
    } else {
        printf("%d nao eh primo\n", n);
    }

    return 0;
}