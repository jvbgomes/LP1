#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char str[100] = {0};
    size_t qtd = 0;
    size_t i;

    printf("Digite uma string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) { // le a string, garantindo que nao passe o limite do buffer e verifica se a leitura foi bem-sucedida.
        str[strcspn(str, "\n")] = '\0'; // Remove o caractere de nova linha, se presente.

        for (i = 0; str[i] != '\0'; i++) { // varre a string ate o caractere nulo.
            if (!isspace((unsigned char)str[i])) { //Verifica se o caractere é um blank space.
                qtd++;
            }
        }

        printf("A string digitada foi: %s\n", str);
        printf("Quantidade de caracteres: %zu\n", qtd);
    }

    return 0;
}