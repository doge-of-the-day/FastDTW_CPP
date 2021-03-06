#ifndef DTW_HPP
#define DTW_HPP
#include <vector>
#include <limits>
#include <complex>
#include <assert.h>

#include "dtw.h"
#include "distances.hpp"
#include "path.h"
#include "mask.h"

namespace fastdtw_cpp {
namespace dtw {
template<typename T>
void trace(const T            *data,
           const unsigned int  rows,
           const unsigned int  cols,
           path::WarpPath<T>  &path)
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

template<typename T>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
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
    T *distances = new T[rows * cols];
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
            T cost      (distances::def_distance<T>(siga_ptr[y], sigb_ptr[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols + x + 1] =
                    cost + std::min(insertion, std::min(deletion, match));

        }
    }
    distance = distances[rows * cols - 1];
    delete[] distances;
}

template<typename T>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           path::WarpPath<T>    &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(signal_a.size());
    unsigned int steps_x(signal_b.size());
    unsigned int rows(steps_y + 1);
    unsigned int cols(steps_x + 1);
    T *distances = new T[rows * cols];
    for(unsigned int i = 1 ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j = 1 ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();

    distances[0] = 0.0;

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
    delete[] distances;
}

template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           path::WarpPath<T> &path)
{
    assert(size_a != 0);
    assert(size_b != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(size_a);
    unsigned int steps_x(size_b);
    unsigned int rows(steps_y + 1);
    unsigned int cols(steps_x + 1);
    T *distances = new T[rows * cols];
    for(unsigned int i = 1 ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j = 1 ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();
    distances[0] = 0.f;

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y = y * cols;
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            T cost      (distances::def_distance(signal_a[y], signal_b[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols + x + 1] = cost + std::min(insertion, std::min(deletion, match));

        }
    }
    path.setDistance(distances[rows * cols - 1]);
    trace(distances, rows, cols, path);
    delete[] distances;
}

template<typename T>
void applyProb(const T* signal_a, const unsigned int size_a,
               const T* signal_b, const unsigned int size_b,
               path::WarpPath<T> &path,
               double &distr)
{
    auto x = 1;
    assert(size_a != 0);
    assert(size_b != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(size_a);
    unsigned int steps_x(size_b);
    unsigned int rows(steps_y + 1);
    unsigned int cols(steps_x + 1);
    T *distances = new T[rows * cols];
    for(unsigned int i = 1 ; i < rows ; ++i)
        distances[i * cols] = std::numeric_limits<T>::infinity();
    for(unsigned int j = 1 ; j < cols ; ++j)
        distances[j] = std::numeric_limits<T>::infinity();
    distances[0] = 0.f;

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y = y * cols;
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            T cost      (distances::def_distance(signal_a[y], signal_b[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols + x + 1] = cost + std::min(insertion, std::min(deletion, match));

        }
    }
    path.setDistance(distances[rows * cols - 1]);
    trace(distances, rows, cols, path);
    delete[] distances;
}


template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           const Mask &mask,
           path::WarpPath<T> &path)
{
    assert(size_a != 0);
    assert(size_b != 0);
    assert(mask.size == size_a * size_b);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(size_a);
    unsigned int steps_x(size_b);
    unsigned int rows_distance(steps_y + 1);
    unsigned int cols_distance(steps_x + 1);
    unsigned int cols_mask(size_b);

    T *distances = new T[rows_distance * cols_distance];
    for(unsigned int i = 0 ; i < rows_distance ; ++i)
        for(unsigned int j = 0 ; j < cols_distance ; ++j)
            distances[i * cols_distance + j] = std::numeric_limits<T>::infinity();
    distances[0] = 0.f;

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y(y * cols_distance);
        int pos_m(y * cols_mask);
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            if(mask.data[pos_m + x]) {
                T cost      (distances::def_distance(signal_a[y], signal_b[x]));
                T insertion (distances[pos_y + x + 1]);
                T deletion  (distances[pos_y + cols_distance + x]);
                T match     (distances[pos_y + x]);
                distances[pos_y + cols_distance + x + 1] = cost + std::min(insertion, std::min(deletion, match));
            }
        }
    }
    path.setDistance(distances[rows_distance * cols_distance - 1]);
    trace(distances, rows_distance, cols_distance, path);
    delete[] distances;
}


template<typename T>
void apply(const std::vector<T>    &signal_a,
           const std::vector<T>    &signal_b,
           const Mask              &mask,
           path::WarpPath<T>       &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    assert(mask.size == signal_a.size() * signal_b.size());
    /// signal_a is rows
    /// signal_b is cols
    unsigned int steps_y(signal_a.size());
    unsigned int steps_x(signal_b.size());
    unsigned int rows_distance(steps_y + 1);
    unsigned int cols_distance(steps_x + 1);
    unsigned int cols_mask(signal_b.size());

    T *distances = new T[rows_distance * cols_distance];
    for(unsigned int i = 0 ; i < rows_distance ; ++i)
        for(unsigned int j = 0 ; j < cols_distance ; ++j)
            distances[i * cols_distance + j] = std::numeric_limits<T>::infinity();
    distances[0] = 0.f;

    const T *siga_ptr(signal_a.data());
    const T *sigb_ptr(signal_b.data());

    for(unsigned int y = 0 ; y < steps_y; ++y) {
        int pos_y = y * cols_distance;
        int pos_m = y * cols_mask;
        for(unsigned int x = 0 ; x < steps_x; ++x) {
            if(mask.data[pos_m + x]) {
                T cost      (distances::def_distance(siga_ptr[y], sigb_ptr[x]));
                T insertion (distances[pos_y + x + 1]);
                T deletion  (distances[pos_y + cols_distance + x]);
                T match     (distances[pos_y + x]);
                distances[pos_y + cols_distance + x + 1] = cost + std::min(insertion, std::min(deletion, match));
            }
        }
    }
    path.setDistance(distances[rows_distance * cols_distance - 1]);
    trace(distances, rows_distance, cols_distance, path);
    delete[] distances;
}

template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           const unsigned int* min_xs,
           const unsigned int* max_xs,
           const unsigned int  indeces,
           path::WarpPath<T> &path)
{
    assert(size_a != 0);
    assert(size_b != 0);
    assert(indeces == size_a);
    /// signal_a is rows
    /// signal_b is cols

    unsigned int rows_distance(size_a + 1);
    unsigned int cols_distance(size_b + 1);
    T *distances = new T[rows_distance * cols_distance];
    for(unsigned int i = 0 ; i < rows_distance ; ++i)
        for(unsigned int j = 0 ; j < cols_distance ; ++j)
            distances[i * cols_distance + j] = std::numeric_limits<T>::infinity();
    distances[0] = 0.f;

    for(unsigned int it(0) ; it < indeces ; ++it) {
        int pos_y(it * cols_distance);
        int max_x(max_xs[it]);
        for(unsigned int x(min_xs[it]) ; x <= max_x ; ++x) {
            T cost      (distances::def_distance(signal_a[it], signal_b[x]));
            T insertion (distances[pos_y + x + 1]);
            T deletion  (distances[pos_y + cols_distance + x]);
            T match     (distances[pos_y + x]);
            distances[pos_y + cols_distance + x + 1] = cost + std::min(insertion, std::min(deletion, match));
        }
    }

    path.setDistance(distances[rows_distance * cols_distance - 1]);
    trace(distances, rows_distance, cols_distance, path);
    delete[] distances;
}
}
}
#endif // DTW_HPP
