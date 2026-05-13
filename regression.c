#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int rows = 1000;
    int columns = 15;
    srand((unsigned int)time(NULL)); 

    float (*data)[columns] = malloc(rows * columns * sizeof(float));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if (j == 14) {
                data[i][j] = rand() % 2;  
            } else {
                data[i][j] = ((float)rand() / (float)RAND_MAX) * (2-0);
            }
        }
    }

    for (int i = 0; i < rows; i++){
        printf("value[%d][14]: %f\n", i, data[i][14]);
        
    }
}
