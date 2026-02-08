# include <stdio.h>
# include <string.h>

int main() {
    int option;

    printf("Which cypher would you like to use?\n");
    printf("Digite 1 para Caesar cypher\n");
    printf("Digite 2 para XOR\n");
    printf("Digite 3 Vinegere\n");

    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Please type in a number\n");
            while (getchar() != '\n');
            continue;
        }

        if (option > 3 || option < 1) {
            printf("Only 1, 2 or 3 are valid inputs\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    switch (option) {
        case 1: {
            printf("Caesar Cypher, to be implemented\n");
            break;
        }

        case 2: {
            printf("XOR com chave repetida, to be implemented\n");
            break;
        }

        case 3: {
            printf("Vinegere, to be implemented\n");
            break;
        }

    } 
}