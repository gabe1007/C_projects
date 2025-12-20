#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int number = 0;
    float result = 0.0;
    float rounded_result = 0.0;

    printf("Enter the number of grades: ");
    scanf("%d", &number);

    while (number <= 0 || number > 5) {
        printf("Please enter a valid number of grades (1-5): ");
        scanf("%d", &number);
    }

    float *grades = malloc(number * sizeof(float));

    if (grades == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < number; i++) {
        while (1) {
            printf("Enter grade %d (0-10): ", i + 1);
            
            if (scanf("%f", &grades[i]) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // limpa letras do buffer
                continue;
            }
            if (grades[i] >= 0 && grades[i] <= 10) {
                result += grades[i];
                break;
            } else {
                printf("Invalid grade. Please enter a grade between 0 and 10.\n");
            }
        }
    }

    result /= number;
    rounded_result = round(result);
    printf("The rounded average is: %.2f\n", rounded_result);
    
    // Free the allocated memory
    free(grades);    
    return 0;
}
