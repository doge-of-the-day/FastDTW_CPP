#include <dtw_c/dtw_c.h>

#include <assert.h>
#include <math.h>

void apply_fdtw_c(const float *seq_a, const unsigned int size_a,
                 const float *seq_b, const unsigned int size_b,
                 double *distance)
{
//    assert(signal_a.size() != 0);
//    assert(signal_b.size() != 0);
//    unsigned int rows(size_a + 1);
//    unsigned int cols(size_b + 1);
//    double      *distances = new double[rows * cols];
//    memset(distances, 0, rows * cols * sizeof(double));

}

void apply_ddtw_c(const double *seq_a, const unsigned int size_a,
                 const double *seq_b, const unsigned int size_b,
                 double *distance)
{
//    assert(signal_a.size() != 0);
//    assert(signal_b.size() != 0);
//    unsigned int rows(size_a + 1);
//    unsigned int cols(size_b + 1);
//    double      *distances = new double[rows * cols];
//    memset(distances, 0, rows * cols * sizeof(double));

//    for(unsigned int i = 1 ; i < rows ; ++i)
//        distances[i * cols] = INFINITY;
//    for(unsigned int j = 1 ; j < cols ; ++j)
//        distances[j] = INFINITY;

}





//void apply(const std::vector<T> &signal_a,
//           const std::vector<T> &signal_b,
//           T &distance)
//{
//    /// signal_a is rows
//    /// signal_b is cols

//    for(unsigned int i = 1 ; i < rows ; ++i)
//        distances[i * cols] = std::numeric_limits<T>::infinity();
//    for(unsigned int j = 1 ; j < cols ; ++j)
//        distances[j] = std::numeric_limits<T>::infinity();

//    distances[0] = 0.0;

//    const T *siga_ptr(signal_a.data());
//    const T *sigb_ptr(signal_b.data());

//    for(unsigned int y = 0 ; y < steps_y; ++y) {
//        int pos_y = y * cols;
//        for(unsigned int x = 0 ; x < steps_x; ++x) {
//            T cost      (distances::def_distance(siga_ptr[y], sigb_ptr[x]));
//            T insertion (distances[pos_y + x + 1]);
//            T deletion  (distances[pos_y + cols + x]);
//            T match     (distances[pos_y + x]);
//            distances[pos_y + cols + x + 1] =
//                    cost + std::min(insertion, std::min(deletion, match));

//        }
//    }
//    distance = distances[rows * cols - 1];
//    delete[] distances;
//}
