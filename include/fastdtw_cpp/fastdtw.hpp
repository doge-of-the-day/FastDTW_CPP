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

template<typename T>
void std(const std::vector<T> &signal_a, const std::vector<T> &signal_b,
         const unsigned int radius,
         path::WarpPath<T> &path,
         const unsigned int adaption = 0)
{
    /// signal_a is rows
    /// signal_b is cols
    /// step 1: build the pyramid
    unsigned int min_size(radius + 2);
    unsigned int adapt_radius(radius);
    utils::SignalPyramid<T, 2> pyr_a(signal_a, min_size);
    utils::SignalPyramid<T, 2> pyr_b(signal_b, min_size);

    /// step 2: eval dtw for lowest resolution level
    int last(std::min(pyr_a.levels(), pyr_b.levels())
                      - 1);

    path::WarpPath<T> sub_path;
    unsigned int size_a = pyr_a.levelSize(last);
    unsigned int size_b = pyr_b.levelSize(last);
    dtw::std(pyr_a.levelPtr(last), size_a,
             pyr_b.levelPtr(last), size_b,
             sub_path);

    /// step 3: project path from level to level
//    std::ofstream out("/tmp/data.txt");
    --last;
    for(int i(last) ; i > -1 ; --i) {
        adapt_radius += adaption;

        /// project last path to current level
        projection::Projection p(size_a, size_b, 2);
        p.project(sub_path, adapt_radius);
        /// get current signals
        size_a = pyr_a.levelSize(i);
        size_b = pyr_b.levelSize(i);


//        for(int y = 0 ; y < size_b ; ++y) {
//            int pos = y * size_a;
//            for(int x = 0 ; x < size_a ; ++x) {
//                out << (int) p.data().at(pos + x) << " ";
//            }
//            out << std::endl;
//        }
//        out << std::endl << std::endl;

        sub_path = path::WarpPath<T>();
        dtw::std(pyr_a.levelPtr(i), size_a,
                 pyr_b.levelPtr(i), size_b,
                 p.data(),
                 sub_path);
    }
//    out.close();
    path = sub_path;
}
}
}

#endif // FASTDTW_CPP_HPP
