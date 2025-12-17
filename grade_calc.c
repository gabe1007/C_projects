#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int number = 0;

    printf("Enter the number of grades: ");
    scanf("%d", &number);

    int *grades = malloc(number * sizeof(int));

    if (grades == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < number; i++) {
        printf("Enter grade %d: ", i + 1);
        scanf(" %d", &grades[i]);
    }

    // Print the array
    for (int i = 0; i < number; i++) {
        printf("grades[%d] = %d\n", i, grades[i]);
    }

    // Free the allocated memory
    free(grades);    
    return 0;
}