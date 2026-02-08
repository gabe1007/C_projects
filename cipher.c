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
            char word[256];
            char buffer[256];
            int escolha;
            int i;

            printf("1 - Encode\n");
            printf("2 - Decode\n");

            while (1) {
                if (scanf("%d", &escolha) != 1) {
                    printf("Only numbers, please");
                    while (getchar() != '\n');
                    continue;
                }

                if (escolha < 1 || escolha > 2) {
                    printf("Only choose 1 or 2");
                    while(getchar() != '\n');
                    continue;
                }
                break;
            }

            if (escolha == 1) {
                while (getchar() != '\n'); // Clear the newline left by scanf
                printf("Type in the word you want to encode\n");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                for (i = 0; word[i] != '\0'; i++){
                    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        buffer[i] = word[i] + 3;
                    } else {
                        buffer[i] = word[i];
                    }
                }
                buffer[i] = '\0'; 

            } else {
                while (getchar() != '\n');
                printf("Type in the word you want to decode\n");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                for (i = 0; word[i] != '\0'; i++){
                    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        buffer[i] = word[i] - 3;
                    } else {
                        buffer[i] = word[i];
                    }
                }
                buffer[i] = '\0';
            }

            printf("%s\n", buffer);
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
