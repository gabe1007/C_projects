# include <stdio.h>
# include <string.h>
# include <ctype.h>

int main() {
    char input[256];

    printf("Type in the expression\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i]) != 0) {
            printf("We found a number %c\n", input[i]);
        }
    }
}
