#ifndef DTW_HPP
#define DTW_HPP
#include <vector>
#include <limits>
#include <complex>
#include <assert.h>

#include "distances.hpp"
#include "path.hpp"

namespace fastdtw_cpp {
namespace dtw {
/**
 * @brief Trace a path in a cost matrix.
 * @param data      data ptr to the cost matrix
 * @param rows      the width of the data matrix
 * @param cols      the height of the data matrix
 * @param path      the path to written to
 */
template<typename T>
void trace(const T *data, const unsigned int rows, const unsigned int cols,
           path::WarpPath<T> &path)
{
    unsigned int x(0);
    unsigned int y(0);
    unsigned int it_x(1);
    unsigned int it_y(1);
    unsigned int last_x(cols - 1);
    unsigned int last_y(rows - 1);

    while(it_y < rows || it_x < cols){
        unsigned int pos(it_y * cols + it_x);
        T right(it_x < last_x ? data[pos + 1]     : std::numeric_limits<T>::infinity());
        T down (it_y < last_y ? data[pos + cols]  : std::numeric_limits<T>::infinity());
        T diag (it_x < last_x && it_y < last_y ? data[pos + cols + 1] : std::numeric_limits<T>::infinity());
        T min  (std::min(right, std::min(diag, down)));

        path.push_back(x,y);

        if(diag == min) {
            ++y;
            ++x;
            ++it_y;
            ++it_x;
        } else if (down == min) {
            ++y;
            ++it_y;
        } else {
            ++x;
            ++it_x;
        }
    }
}

/**
 * @brief Standard dtw algorithm only calculating the distance.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param distance      the warp distance
 */
template<typename T>
void std(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         T &distance)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(signal_a.size());
    unsigned int steps_x(signal_b.size());
    unsigned int rows(steps_y + 1);
    unsigned int cols(steps_x + 1);
    T distances[rows * cols];

    for(unsigned int i = 1 ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j = 1 ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();

    distances[0] = 0.f;

    const T *siga_ptr(signal_a.data());
    const T *sigb_ptr(signal_b.data());

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y = y * cols;
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            T cost      (distances::def_distance(siga_ptr[y], sigb_ptr[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols + x + 1] = cost + std::min(insertion, std::min(deletion, match));

        }
    }
    distance = distances[rows * cols - 1];
}

/**
 * @brief Standard dtw algorithm only calculating the distance.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param distance      the warp distance
 * @param path          the warp path
 */
template<typename T>
void std(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         path::WarpPath<T> &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(signal_a.size());
    unsigned int steps_x(signal_b.size());
    unsigned int rows(steps_y + 1);
    unsigned int cols(steps_x + 1);
    T distances[rows * cols];

    for(unsigned int i = 1 ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j = 1 ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();

    distances[0] = 0.f;

    const T *siga_ptr(signal_a.data());
    const T *sigb_ptr(signal_b.data());

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y = y * cols;
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            T cost      (distances::def_distance(siga_ptr[y], sigb_ptr[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols + x + 1] = cost + std::min(insertion, std::min(deletion, match));

        }
    }
    path.setDistance(distances[rows * cols - 1]);
    trace(distances, rows, cols, path);
}

template<typename T>
void std(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const std::vector<bool> &mask,
         path::WarpPath<T> &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    assert(path.empty());
    /// signal_a is rows
    /// signal_b is cols
    unsigned int rows(signal_a.size() + 1);
    unsigned int cols(signal_b.size() + 1);
    T distances[rows * cols];

    for(unsigned int i(1) ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j(1) ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();

    distances[0] = 0.f;

    const T *siga_ptr(signal_a.data());
    const T *sigb_ptr(signal_b.data());

    for(unsigned int i(1) ; i < rows ; ++i) {
        int i_min((i - 1) * cols);

        for(unsigned int j(1) ; j < cols ; ++j) {
            int   j_min     (j - 1);
            T cost      (distances::def_distance(siga_ptr[i], sigb_ptr[j]));
            T insertion (distances[i_min  + j]);
            T deletion  (distances[i_min + cols + j_min]);
            T match     (distances[i_min + j_min]);
            distances[i_min + cols + j] = cost + std::min(insertion, std::min(deletion, match));
        }
    }

    path.setDistance(distances[rows * cols - 1]);
    trace(distances, rows, cols, path);
}




template<typename T>
void loc(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const int adapt_window, T &distance) {
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols
    int rows(signal_a.size() + 1);
    int cols(signal_b.size() + 1);
    std::vector<T> distances;
    distances.resize(rows * cols, std::numeric_limits<T>::infinity());

    T *dist_ptr(distances.data());
    dist_ptr[0] = 0.f;

    int w(std::max(adapt_window, (const int) std::abs(cols - rows)));

    const T *siga_ptr(signal_a.data());
    const T *sigb_ptr(signal_b.data());

    for(int i = 1 ; i < rows ; ++i) {
        int i_min(i - 1);
        for(int j = std::max(1, i - w) ; j < std::min(cols, i + w + 1); ++j) {
            int   j_min     (j - 1);
            T cost      (distances::def_distance(siga_ptr[i], sigb_ptr[j]));
            T insertion (dist_ptr[i_min * cols + j]);
            T deletion  (dist_ptr[i_min + cols + j_min]);
            T match     (dist_ptr[i_min * cols + j_min]);
            dist_ptr[i * cols + j] = cost + std::min(insertion, std::min(deletion, match));
        }
    }

    distance = dist_ptr[rows * cols - 1];
}
}
}
#endif // DTW_HPP
