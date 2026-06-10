#include <stdlib.h>

#define COLUMNS 10

static inline int get_random_index(int n) {
    int limit = RAND_MAX - (RAND_MAX % n);
    int rnd;

    do {
        rnd = rand();
    } while (rnd >= limit);

    return rnd % n;
}

static inline void shuffle_matrix(float (*data)[COLUMNS], int rows, int cols) {
    // Shuffle rows in-place: Fisher-Yates on row indices
    for (int i = rows - 1; i > 0; i--) {
        int j = get_random_index(i + 1);
        // Swap entire rows i and j
        for (int k = 0; k < cols; k++) {
            float temp = data[i][k];
            data[i][k] = data[j][k];
            data[j][k] = temp;
        }
    }
}
