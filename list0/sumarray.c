#include <stdio.h>

int main() {
    int num[5];
    int sum = 0;

    printf("Digite 5 numeros: ");

    for(int i = 0; i < 5; i++) {
        scanf("%d", &num[i]);
        sum += num[i];
    }
    printf("A soma dos numeros foi: %d\n", sum);
    
    return 0;
}