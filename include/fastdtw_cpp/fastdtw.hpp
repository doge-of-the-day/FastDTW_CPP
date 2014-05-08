#ifndef FASTDTW_CPP_HPP
#define FASTDTW_CPP_HPP

#include "dtw.hpp"
#include "utils.hpp"
#include "projection.hpp"
#include <iostream>
#include <fstream>
#include <ostream>

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
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           const unsigned int radius,
           path::WarpPath<T> &path,
           const unsigned int adaption = 0)
{
    /// signal_a is rows
    /// signal_b is cols
    unsigned int min_size(radius + 2);
    unsigned int adapt_radius(radius);
    utils::SignalPyramid<T, 2> pyr_a(signal_a, min_size);
    utils::SignalPyramid<T, 2> pyr_b(signal_b, min_size);

    int last(std::min(pyr_a.levels(), pyr_b.levels())
                      - 1);

    path::WarpPath<T> sub_path;
    unsigned int size_a = pyr_a.levelSize(last);
    unsigned int size_b = pyr_b.levelSize(last);
    dtw::apply(pyr_a.levelPtr(last), size_a,
               pyr_b.levelPtr(last), size_b,
               sub_path);

    --last;
    for(int i(last) ; i > -1 ; --i) {
        adapt_radius += adaption;

        projection::Projection p(size_a, size_b, 2);
        p.project(sub_path, adapt_radius);
        size_a = pyr_a.levelSize(i);
        size_b = pyr_b.levelSize(i);

        sub_path = path::WarpPath<T>();
        dtw::apply(pyr_a.levelPtr(i), size_a,
                   pyr_b.levelPtr(i), size_b,
                   p.data(),
                   sub_path);
    }
    path = sub_path;
}

template<typename T, unsigned int Radius>
void apply(const std::vector<T> &signal_a,
           const std::vector<T> &signal_b,
           path::WarpPath<T> &path)
{
    /// signal_a is rows
    /// signal_b is cols
    unsigned int min_size(Radius + 2);
    utils::SignalPyramid<T, 2> pyr_a(signal_a, min_size);
    utils::SignalPyramid<T, 2> pyr_b(signal_b, min_size);

    int last(std::min(pyr_a.levels(), pyr_b.levels())
                      - 1);

    path::WarpPath<T> sub_path;
    unsigned int size_a = pyr_a.levelSize(last);
    unsigned int size_b = pyr_b.levelSize(last);
    dtw::apply(pyr_a.levelPtr(last), size_a,
               pyr_b.levelPtr(last), size_b,
               sub_path);

    --last;
    for(int i(last) ; i > -1 ; --i) {
        projection::ProjectionIDC<Radius, 2> p(size_a, size_b);
        p.project(sub_path);
        size_a = pyr_a.levelSize(i);
        size_b = pyr_b.levelSize(i);

        sub_path = path::WarpPath<T>();
        dtw::apply(pyr_a.levelPtr(i), size_a,
                   pyr_b.levelPtr(i), size_b,
                   p.minXPtr(),
                   p.maxXPtr(),
                   p.size(),
                   sub_path);
    }
    path = sub_path;
}
}
}

#endif // FASTDTW_CPP_HPP
