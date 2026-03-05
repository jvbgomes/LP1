#include <stdio.h>

int main() {
    float cel, fah, temp;
    char option;
    printf("Digite a temperatura em Celsius ou Fahrenheit: \n");
    scanf("%f %c", &temp, &option);

    int lidos = scanf("%f %c", &temp, &option);
    if(lidos != 2) {
        printf("Entrada invalida. Por favor, insira um numero seguido de 'C' ou 'F'.\n");
        return 1;
    }

    if(option == 'C' || option == 'c') {
        fah = (temp * 9/5) + 32;
        printf("A temperatura em Fahrenheit e: %.2f\n", fah);
    } else if(option == 'F' || option == 'f') {
        cel = (temp - 32) * 5/9;
        printf("A temperatura em Celsius e: %.2f\n", cel);
    } else {
        printf("Opcao invalida. Use C ou F.\n");
    }

    return 0;
}