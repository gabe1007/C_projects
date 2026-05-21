#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float w[9] = {
    0.8f,
    0.6f,
    -0.75f,
    0.85f,
    -0.55f,
    -0.63f,
    -0.22f,
    0.11f,
    0.22f
};

float label(float *data, int num_features, float *w);

int main() {

    int rows = 1000;
    int columns = 10;
    int num_features = columns - 1;

    srand((unsigned int)time(NULL));

    float (*data)[columns] = malloc(rows * sizeof(*data));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < num_features; j++) {
            data[i][j] = ((float)rand() / (float)RAND_MAX) * 2.0f;
        }
    }

    for (int i = 0; i < rows; i++) {
        data[i][9] = label(data[i], num_features, w);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", data[i][j]);
        }
        printf("\n");
    }

    free(data);

    return 0;
}

float label(float *data, int num_features, float *w) {
    float score = 0.0f;

    for (int i = 0; i < num_features; i++) {
        score += data[i] * w[i];
    }

    float prob = 1.0f / (1.0f + expf(-score));

    if (prob >= 0.5f) return 1.0f; else return 0.0f;
}
