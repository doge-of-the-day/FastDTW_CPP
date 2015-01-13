#include <dtw_c/dtw_c.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

void apply_fdtw_c(const float *seq_a, const unsigned int size_a,
                  const float *seq_b, const unsigned int size_b,
                  double *distance)
{
    assert(size_a != 0);
    assert(size_b != 0);
    unsigned int rows = (size_a + 1);
    unsigned int cols = (size_b + 1);
    double      *distances = malloc(rows * cols * sizeof(double));

    unsigned int i;
    for(i = 1 ; i < cols ; ++i)
        distances[i] = INFINITY;
    for(i = 1 ; i < rows ; ++i)
        distances[i * cols] = INFINITY;
    distances[0] = 0.0;

    unsigned int y;
    unsigned int x;
    int pos_y = 0;
    int pos_y_next = 0;
    double cost;
    double insertion;
    double deletion;
    double match;

    for(y = 0 ; y < size_a; ++y) {
        pos_y_next += cols;
        double *next_dist = distances + pos_y_next + 1;
        for(x = 0 ; x < size_b; ++x, ++next_dist) {
            cost      = (fabs(seq_a[y] - seq_b[x]));
            insertion = (distances[pos_y + x + 1]);
            deletion  = (distances[pos_y + cols + x]);
            match     = (distances[pos_y + x]);
            *next_dist = cost + fmin(insertion, fmin(deletion, match));

        }
        pos_y += cols;
    }
    *distance = distances[rows * cols - 1];
    free(distances);
}

void apply_ddtw_c(const double *seq_a, const unsigned int size_a,
                  const double *seq_b, const unsigned int size_b,
                  double *distance)
{
    assert(size_a != 0);
    assert(size_b != 0);
    unsigned int rows = (size_a + 1);
    unsigned int cols = (size_b + 1);
    double      *distances = malloc(rows * cols * sizeof(double));

    unsigned int i;
    for(i = 1 ; i < cols ; ++i)
        distances[i] = INFINITY;
    for(i = 1 ; i < rows ; ++i)
        distances[i * cols] = INFINITY;
    distances[0] = 0.0;

    unsigned int y;
    unsigned int x;
    int pos_y = 0;
    int pos_y_next = 0;
    double cost;
    double insertion;
    double deletion;
    double match;

    for(y = 0 ; y < size_a; ++y) {
        pos_y_next += cols;
        double *next_dist = distances + pos_y_next + 1;
        for(x = 0 ; x < size_b; ++x, ++next_dist) {
            cost      = (fabs(seq_a[y] - seq_b[x]));
            insertion = (distances[pos_y + x + 1]);
            deletion  = (distances[pos_y + cols + x]);
            match     = (distances[pos_y + x]);
            *next_dist = cost + fmin(insertion, fmin(deletion, match));

        }
        pos_y += cols;
    }
    *distance = distances[rows * cols - 1];
    free(distances);
}
