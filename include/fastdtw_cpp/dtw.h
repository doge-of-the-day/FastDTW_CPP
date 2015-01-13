#ifndef DTW_H
#define DTW_H

#include <vector>
#include "path.h"
#include "mask.h"

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
void trace(const T            *data,
           const unsigned int  rows,
           const unsigned int  cols,
           path::WarpPath<T>  &path);

/**
 * @brief Standard dtw algorithm only calculating the distance.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param distance      the warp distance
 */
template<typename T>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           T &distance);

/**
 * @brief Standard dtw algorithm only calculating the distance.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param path          the warp path
 */
template<typename T>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           path::WarpPath<T>    &path);

/**
 * @brief Apply the dtw using arrays and element counts.
 * @param signal_a      first signal array
 * @param size_a        size of first signal array
 * @param signal_b      second signal array
 * @param size_b        size of second signal array
 * @param path          the resulting path
 */
template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           path::WarpPath<T> &path);

/**
 * @brief Apply the dtw using arrays and element counts and mask.
 * @param signal_a      first signal array
 * @param size_a        size of first signal array
 * @param signal_b      second signal array
 * @param size_b        size of second signal array
 * @param mask          the mask for leaving out the update for certain cells
 * @param path          the resulting path
 */
template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           const Mask &mask,
           path::WarpPath<T> &path);
/**
 * @brief Apply the normal dtw using vectors and given a mask.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param mask          the mask to leave out updates
 * @param path          the resulting path
 */
template<typename T>
void apply(const std::vector<T>    &signal_a,
           const std::vector<T>    &signal_b,
           const Mask              &mask,
           path::WarpPath<T>       &path);

template<typename T>
void apply(const T* signal_a, const unsigned int size_a,
           const T* signal_b, const unsigned int size_b,
           const unsigned int* min_xs,
           const unsigned int* max_xs,
           const unsigned int  indeces,
           path::WarpPath<T> &path);

}
}
#endif // DTW_H

