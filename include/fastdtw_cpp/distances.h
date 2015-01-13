#ifndef DISTANCES_H
#define DISTANCES_H
namespace fastdtw_cpp {
namespace distances {
/**
 * @brief Distance functions for dtw.
 * @param s     first operand
 * @param t     second operand
 * @return
 */
template<typename T>
T def_distance(const T s, const T t);
}
}

#endif // DISTANCES_H

