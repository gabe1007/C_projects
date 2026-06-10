#include <stdlib.h>
#include <math.h>
#include <time.h>

static inline void create_weights(float *weights) {
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
