#ifndef FASTDTW_CPP_HPP
#define FASTDTW_CPP_HPP

#include "dtw.hpp"
#include "utils.hpp"

namespace fastdtw_cpp {
namespace fastdtw {
template<typename T>
void arr(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const unsigned int radius,
         path::WarpPath<T> &path)
{
    arr_rec(signal_a, signal_b, radius, 2,  path);
}

template<typename T>
void arr_rec(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
             const unsigned int radius, const unsigned int shrink_fac,
             path::WarpPath<T> &path)
{
    assert(signal_a.size() != 0);
    assert(signal_b.size() != 0);
    /// signal_a is rows
    /// signal_b is cols

    unsigned int min_coarsest_res = radius + 2;

    if(signal_a.size() < min_coarsest_res || signal_b.size() < min_coarsest_res) {
        dtw::std(signal_a, signal_b, path);
    } else {
        std::vector<T> shrunk_a;
        std::vector<T> shrunk_b;
        utils::shrink_static<T,2>(signal_a, shrunk_a);
        utils::shrink_static<T,2>(signal_b, shrunk_b);
        path::WarpPath<T> sub_path;
        fastdtw::arr(shrunk_a, shrunk_b, radius, sub_path);
        window(signal_a, signal_b, shrunk_a, shrunk_b, shrink_fac, sub_path);



//        final SearchWindow window = new ExpandedResWindow(tsI, tsJ, shrunkI, shrunkJ,
//                                                          FastDTW.getWarpPathBetween(shrunkI, shrunkJ, searchRadius, distFn),
//                                                          searchRadius);


        /// shrink
    }
}


template<typename T>
void window(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
            const std::vector<T> &shrunk_a, const std::vector<T> &shrunk_b,
            const unsigned int shrink_fac,
            const path::WarpPath<T> &path)
{

    unsigned int size = path.size();
    for(unsigned int i = 0 ; i < size ; ++i) {
        unsigned int x = path.x(i);
        unsigned int y = path.y(i);


    }


}
}
}

#endif // FASTDTW_CPP_HPP
