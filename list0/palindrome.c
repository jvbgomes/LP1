#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        while (left < right && !isalpha((unsigned char)str[left])) left++;
        while (left < right && !isalpha((unsigned char)str[right])) right--;

        if (tolower((unsigned char)str[left]) != tolower((unsigned char)str[right]))
            return 0;

        left++;
        right--;
    }
    return 1;
}

int main() {
    char str[100];
    printf("Digite uma palavra ou frase: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    if (isPalindrome(str)) {
        printf("\"%s\" e um palindromo.\n", str);
    } else {
        printf("\"%s\" nao e um palindromo.\n", str);
    }

    return 0;
}
