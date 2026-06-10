#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define ROWS 1000
#define COLUMNS 10  
#define COLS_DATASET 9
#include "shuffle.h"
#include "create_weights.h"

float w_features[9] = {
    0.8,
    0.6,
    -0.75,
    0.85,
    -0.95,
    -0.63,
    -0.22,
    0.11,
    0.22
};

float weights[9];

float sigmoid(float value);
float label(float *data, int num_features, float *w);
void create_dataset(int rows, int columns, float (*data)[columns]);
void create_weights(float *weights);
int get_random_index(int n);
void shuffle_matrix(float (*data)[COLUMNS], int rows, int cols);
void split(
    int cols, 
    int columns, 
    int size_y, 
    float (*X_train)[cols], 
    float (*X_test)[cols], 
    float (*y_train)[size_y], 
    float (*y_test)[size_y], 
    float (*data)[columns], 
    int train_size, 
    int test_size
);

int main(void)
{
    int test_size = ROWS / 5;
    int train_size = ROWS - test_size;
    int size_y = 1;

    srand((unsigned int)time(NULL));

    float (*data)[COLUMNS] = malloc(ROWS * sizeof(*data));
    float (*X_train)[COLS_DATASET] = malloc(train_size * sizeof(*X_train));
    float (*X_test)[COLS_DATASET] = malloc(test_size * sizeof(*X_test));
    float (*y_train)[size_y] = malloc(train_size * sizeof(*y_train));
    float (*y_test)[size_y] = malloc(test_size * sizeof(*y_test));

    if (data == NULL || X_train == NULL || X_test == NULL || y_train == NULL || y_test == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    create_dataset(ROWS, COLUMNS, data);

    create_weights(weights);

    shuffle_matrix(data, ROWS, COLUMNS);

    split(COLS_DATASET, COLUMNS, size_y, X_train, X_test, y_train, y_test, data, train_size, test_size);

    for (int i = 0; i < train_size; i++) {
        printf("%f ", y_train[i][0]);
        printf("\n");
    }

    free(data);
    free(X_train);
    free(X_test);
    free(y_train);
    free(y_test);

    return 0;
}

void split(
    int cols, 
    int columns, 
    int size_y, 
    float (*X_train)[cols], 
    float (*X_test)[cols], 
    float (*y_train)[size_y], 
    float (*y_test)[size_y], 
    float (*data)[columns], 
    int train_size, 
    int test_size
){
    for (int i = 0; i < train_size; i++){
        for (int j = 0; j < cols; j++){
            X_train[i][j] = data[i][j];
        }
        y_train[i][0] = data[i][columns - 1];
    }
    for (int i = train_size; i < train_size + test_size; i++){
        for (int j = 0; j < cols; j++){
            X_test[i - train_size][j] = data[i][j];
        }
        y_test[i - train_size][0] = data[i][columns - 1];
    }
}


float sigmoid(float value) {
    return 1 / (1 + expf(-value));
}

float label(float *data, int num_features, float *w_features) {
    float score = 0;

    for (int i = 0; i < num_features; i++) {
        score += data[i] * w_features[i];
    }

    return sigmoid(score) >= 0.5 ? 1 : 0;
}

void create_dataset(int rows, int columns, float (*data)[columns]) {
    int num_features = columns - 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < num_features; j++) {
            data[i][j] = ((float)rand() / RAND_MAX) * 2;
        }
    }

    for (int i = 0; i < rows; i++) {
        data[i][columns - 1] = label(data[i], num_features, w_features);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", data[i][j]);
        }
        printf("\n");
    }
}
