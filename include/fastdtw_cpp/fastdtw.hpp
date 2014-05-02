#ifndef FASTDTW_CPP_HPP
#define FASTDTW_CPP_HPP

#include "dtw.hpp"
#include "utils.hpp"

namespace fastdtw_cpp {
namespace fastdtw {
/// non-recursive
template<typename T>
void pyr(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const unsigned int radius,
         path::WarpPath<T> path)
{
    /// step 1: build the pyramid
    /// step 2: eval dtw for highest level
    /// step 3: project path from level to level
    /// step 4: only evaluate projected cells of path in lower resolution
}

namespace {
template<typename T>
void rec_step(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
              const unsigned int radius, const unsigned int shrink_level,
              path::WarpPath<T> &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols
    unsigned int min_coarsest_res = radius + 2;
    unsigned int size_a = signal_a.size();
    unsigned int size_b = signal_b.size();

    if(size_a < min_coarsest_res || size_b < min_coarsest_res) {
        dtw::std(signal_a, signal_b, path);
    } else {
        std::vector<T> shrunk_a, shrunk_b;
        utils::shrink_static<T,2>(signal_a, shrunk_a);
        utils::shrink_static<T,2>(signal_b, shrunk_b);
        path::WarpPath<T> sub_path;
        rec_step(shrunk_a, shrunk_b, radius, shrink_level * 2, sub_path);
        /// project resulting path and make new search window
        /// search by evaluating the projected cells
    }

}
}

/// recursive
template<typename T>
void rec(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const unsigned int radius,
         path::WarpPath<T> &path)
{
    rec_step(signal_a, signal_b, radius, 2, path);
}
}
}

#endif // FASTDTW_CPP_HPP
