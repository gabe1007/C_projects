#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

void display_game_info(int rows, int cols, char (*matrix)[cols]);

int main() { 
    int rows = 3;
    int cols = 3;

    int row_choice;
    int col_choice;
    int game_choice;

    char value_added;
    char name_player_1[50];
    char name_player_2[50];
    bool turn_player_1 = true;

    char (*matrix)[cols] = malloc(rows * cols * sizeof(char));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = ' ';
        }
    }

    display_game_info(rows, cols, matrix);

    printf("Enter name for Player 1: ");
    if (scanf("%49s", name_player_1) != 1) {
        printf("Invalid input for Player 1 name.\n");
        return 1;
    }
    
    printf("Enter name for Player 2: ");
    if (scanf("%49s", name_player_2) != 1) {
        printf("Invalid input for Player 2 name.\n");
        return 1;
    }

    while (1) {
        if (turn_player_1) {
            printf("%s's turn (x)\n", name_player_1);
        } else {
            printf("%s's turn (o)\n", name_player_2);
        }

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
            printf("Make your choice. Just remember: %s is 'x' and %s is 'o': ",name_player_1, name_player_2);

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

        if (turn_player_1 && value_added != 'x') {
            printf("Player 1 must enter 'x'. Try again.\n");
            continue;
        } else if (!turn_player_1 && value_added != 'o') {
            printf("Player 2 must enter 'o'. Try again.\n");
            continue;
        }

        matrix[row_choice][col_choice] = value_added;

        for (int i = 0; i < cols; i++) {
            if (matrix[i][0] == matrix[i][1] && 
                matrix[i][1] == matrix[i][2] && 
                matrix[i][0] != ' ') {
                printf("You win %s!\n", turn_player_1 ? name_player_1 : name_player_2);
                return 0;
            }
        }

        for (int i = 0; i < rows; i++) {
            if (matrix[0][i] == matrix[1][i] && 
                matrix[1][i] == matrix[2][i] && 
                matrix[0][i] != ' ') {
                printf("You win %s!\n", turn_player_1 ? name_player_1 : name_player_2);
                return 0;
            }
        }

        if (matrix[0][0] == matrix[1][1] && 
            matrix[1][1] == matrix[2][2] && 
            matrix[0][0] != ' ') {
            printf("You win %s!\n", turn_player_1 ? name_player_1 : name_player_2);
            return 0;
        }

        if (matrix[0][2] == matrix[1][1] && 
            matrix[1][1] == matrix[2][0] && 
            matrix[0][2] != ' ') {
            printf("You win %s!\n", turn_player_1 ? name_player_1 : name_player_2);
            return 0;
        }

        system("clear");

        printf("\n");
        printf("     0   1   2\n\n");
        for (int i = 0; i < rows; i++) {
            printf("%d    %c | %c | %c\n", i, matrix[i][0], matrix[i][1], matrix[i][2]);
            if (i < rows - 1) {
                printf("   -------------\n");
            }
        }
        printf("\n");

        turn_player_1 = !turn_player_1;
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

