#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <fastdtw_cpp/path.hpp>
#include <fastdtw_cpp/mask.h>

#include <assert.h>
#include <iostream>

namespace fastdtw_cpp {
namespace projection {

template<typename T>
void Projection::project(const path::WarpPath<T> &path,
                         const unsigned int radius)
{
    unsigned int curr_it(0);
    unsigned int next_it(1);
    bool         was_dia(false);
    const unsigned int *x_ptr(path.x_ptr());
    const unsigned int *y_ptr(path.y_ptr());

    while(next_it < path.size()) {
        unsigned int curr_x(x_ptr[curr_it]);
        unsigned int next_x(x_ptr[next_it]);
        unsigned int curr_y(y_ptr[curr_it]);
        unsigned int next_y(y_ptr[next_it]);

        if(next_x > curr_x && next_y > curr_y ){
            if(was_dia)
                diagonal(curr_x, curr_y, 0, radius);
            else {
                diagonalStart(curr_x, curr_y, radius);
                was_dia = true;
            }
        } else {
            block(curr_x, curr_y, radius);
            was_dia = false;
        }
        ++curr_it;
        ++next_it;
    }
    unsigned int last(path.size() - 1);
    block(x_ptr[last], y_ptr[last], radius);
}


}
}

#endif // PROJECTION_HPP
