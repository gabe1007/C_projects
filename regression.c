#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define ROWS 1000
#define COLUMNS 10  

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

int main(void)
{

    srand((unsigned int)time(NULL));

    float (*data)[COLUMNS] = malloc(ROWS * sizeof(*data));

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    create_dataset(ROWS, COLUMNS, data);

    create_weights(weights);

    for (int i = 0; i < 9; i++) {
        printf("Weight %d: %f\n", i, weights[i]);
    }

    shuffle_matrix(data, ROWS, COLUMNS);

    free(data);

    return 0;
}

int get_random_index(int n) {
    int limit = RAND_MAX - (RAND_MAX % n);
    int rnd;

    do {
        rnd = rand();
    } while (rnd >= limit);

    return rnd % n;
}

void shuffle_matrix(float (*data)[COLUMNS], int rows, int cols) {
    int total_elements = rows * cols;
    
    for (int i = total_elements - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = get_random_index(i + 1);
        
        // Map 1D index i to 2D coordinates
        int r_i = i / cols;
        int c_i = i % cols;
        
        // Map 1D index j to 2D coordinates
        int r_j = j / cols;
        int c_j = j % cols;
        
        // In-place swap the elements
        float temp = data[r_i][c_i];
        data[r_i][c_i] = data[r_j][c_j];
        data[r_j][c_j] = temp;
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

void create_weights(float *weights) {
    int mean = 0;
    float std = 0.1;

    for (int i = 0; i < 9; i++) {
        double u1 = (double)rand() / RAND_MAX;
        double u2 = (double)rand() / RAND_MAX;

        // Ensure u1 is not 0 to avoid log(0)
        if (u1 == 0) u1 = 1e-9;
    
        // Box-Muller transform
        double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
        weights[i] = mean + z0 * std;
    }
}
