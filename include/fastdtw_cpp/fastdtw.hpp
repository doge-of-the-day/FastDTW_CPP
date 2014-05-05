#ifndef FASTDTW_CPP_HPP
#define FASTDTW_CPP_HPP

#include "dtw.hpp"
#include "utils.hpp"
#include "projection.hpp"

namespace fastdtw_cpp {
namespace fastdtw {

template<typename T>
void std(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const unsigned int radius,
         path::WarpPath<T> &path)
{
    /// signal_a is rows
    /// signal_b is cols
    /// step 1: build the pyramid
    unsigned int min_size(radius + 2);
    utils::SignalPyramid<T, 2> pyr_a(signal_a, min_size);
    utils::SignalPyramid<T, 2> pyr_b(signal_b, min_size);

    /// step 2: eval dtw for lowest resolution level
    int last(std::min(pyr_a.levels(), pyr_b.levels())
                      - 1);
     std::vector<T> level_a(pyr_a.getLevel(last));
    std::vector<T> level_b(pyr_b.getLevel(last));
    path::WarpPath<T> sub_path;
    dtw::std(level_a, level_b, sub_path);

    /// step 3: project path from level to level
    --last;
    for(int i(last) ; i > -1 ; --i) {
        /// project last path to current level
        projection::Projection p(level_a.size(), level_b.size(), 2);
        p.project(sub_path, radius);
        /// get current signals
        level_a = pyr_a.getLevel(i);
        level_b = pyr_b.getLevel(i);
        sub_path = path::WarpPath<T>();
        dtw::std(level_a, level_b, p.data(), sub_path);
        sub_path.print();
    }
    path = sub_path;
    /// step 4: only evaluate projected cells of path in lower resolution
}

}
}

#endif // FASTDTW_CPP_HPP
