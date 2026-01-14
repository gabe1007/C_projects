#include <stdio.h>
#include <stdlib.h>

void display_game_info(int rows, int cols, char (*matrix)[cols]);

int main() { 
    int rows = 3;
    int cols = 3;

    int row_choice;
    int col_choice;
    int game_choice;

    char player1[50];
    char player2[50];
    char value_added;

    char (*matrix)[cols] = malloc(rows * cols * sizeof(char));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = ' ';
        }
    }

    display_game_info(rows, cols, matrix);

    while (1) {
        printf("Do you want to play? (1 = yes, 0 = no): ");
        if (scanf("%d", &game_choice) != 1 || (game_choice != 0 && game_choice != 1)) {
            printf("Invalid choice. Enter 0 or 1.\n");
            while(getchar() != '\n');
            continue;
        }
        break;
    }

    if (game_choice == 1) {
        while (1) {
            while (1){
                printf("Type the row you want to fill (0-%d): ", rows - 1);
                if (scanf("%d", &row_choice) != 1 || row_choice < 0 || row_choice >= rows) {
                    printf("Invalid row choice.\n");
                    while(getchar() != '\n'); // clear invalid input
                    continue;
                }
                break;
            }

            while (1){
                printf("Type the column you want to fill (0-%d): ", cols - 1);
                if (scanf("%d", &col_choice) != 1 || col_choice < 0 || col_choice >= cols) {
                    printf("Invalid column choice.\n");
                    while(getchar() != '\n'); // clear invalid input
                    continue;
                }
                break;
            }
            
            if (matrix[row_choice][col_choice] != ' ') {
                printf("Cell already occupied. Choose another cell.\n");
                continue;
            }

            while (1) {
                printf("Type the value you want to add (x/o): ");

                if (scanf(" %c", &value_added) != 1) {
                    printf("Invalid value input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (value_added >= 'A' && value_added <= 'Z') {
                    value_added += 32;
                }

                if (value_added != 'x' && value_added != 'o') {
                    printf("Only 'x' or 'o' are allowed.\n");
                    while (getchar() != '\n');
                    continue;
                }

                break;
            }

            matrix[row_choice][col_choice] = value_added;

            for (int i = 0; i < cols; i++) {
                if (matrix[i][0] == matrix[i][1] && 
                    matrix[i][1] == matrix[i][2] && 
                    matrix[i][0] != ' ') {
                    printf("you win!\n");
                    return 0;
                }
            }

            for (int i = 0; i < rows; i++) {
                if (matrix[0][i] == matrix[1][i] && 
                    matrix[1][i] == matrix[2][i] && 
                    matrix[0][i] != ' ') {
                    printf("you win!\n");
                    return 0;
                }
            }

            if (matrix[0][0] == matrix[1][1] && 
                matrix[1][1] == matrix[2][2] && 
                matrix[0][0] != ' ') {
                printf("you win!\n");
                return 0;
            }

            if (matrix[0][2] == matrix[1][1] && 
                matrix[1][1] == matrix[2][0] && 
                matrix[0][2] != ' ') {
                printf("you win!\n");
                return 0;
            }

            printf("\n");
            for (int i = 0; i < rows; i++) {
                printf(" %c | %c | %c\n", matrix[i][0], matrix[i][1], matrix[i][2]);
                if (i < rows - 1) {
                    printf("-----------\n");
                }
            }
            printf("\n");
        }
    } else {
        printf("Goodbye!\n");
    }
    
    free(matrix);
    return 0; 
}

void display_game_info(int rows, int cols, char (*matrix)[cols]) {
    printf("\n=== TIC TAC TOE ===\n");
    printf("Instructions: Choose a row (0-2) and column (0-2) to place your mark (x or o)\n\n");

    // column numbers
    printf("     0    1    2\n");

    // row 0
    printf("\n0       |    | \n");
    printf("   ----------------\n");

    // row 1
    printf("1       |    |  \n");
    printf("   ----------------\n");

    // row 2
    printf("2       |    |  \n");

    printf("\n");
}

