#ifndef FASTDTW_H
#define FASTDTW_H

#include <vector>
#include "path.h"

namespace fastdtw_cpp {
namespace fastdtw {

/**
 * @brief Apply the fast dtw algorithm.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param radius        the radius for path projection
 * @param path          the final warp path
 * @param adaption      enable adaption / a value which will be added
 *                      to the radius each projection layer
 */
template<typename T>
void applyDyn(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           const unsigned int radius,
           path::WarpPath<T> &path);

/**
 * @brief Apply the fast dtw algorithm fixed radius compiled.
 * @param signal_a      the first signal
 * @param signal_b      the second signal
 * @param radius        the radius for path projection
 * @param path          the final warp path
 * @param adaption      enable adaption / a value which will be added
 *                      to the radius each projection layer
 */
template<typename T, unsigned int Radius>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           path::WarpPath<T>    &path);
}
}
#endif // FASTDTW_H

