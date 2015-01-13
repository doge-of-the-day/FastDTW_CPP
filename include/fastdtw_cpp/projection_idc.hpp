#ifndef PROJECTION_IDC_HPP
#define PROJECTION_IDC_HPP

#include "projection_idc.h"

template<unsigned int Radius, unsigned int Scale>
ProjectionIDC::ProjectionIDC<Radius, Scale>(
        const unsigned int src_height,
        const unsigned int src_width,
        const unsigned int off_height = 0,
        const unsigned int off_width = 0) :
    height_(src_height * Scale + off_height),
    width_(src_width * Scale + off_width),
    max_idx_(width_ - 1),
    max_idy_(height_ - 1),
    min_xs_(height_, 0),
    max_xs_(height_, 0),
    min_xs_ptr_(min_xs_.data()),
    max_xs_ptr_(max_xs_.data())
{
    for(unsigned int i(height_ - Scale - Radius) ; i < height_ ; ++i)
        max_xs_ptr_[i] = max_idx_;
}

template<unsigned int Radius, unsigned int Scale>
ProjectionIDC::ProjectionIDC<Radius, Scale>(
        const ProjectionIDC &other) :
    height_(other.height_),
    width_(other.width_),
    max_idx_(other.max_idx_),
    max_idy_(other.max_idy_),
    min_xs_(other.min_xs_),
    max_xs_(other.max_xs_),
    min_xs_ptr_(min_xs_.data()),
    max_xs_ptr_(max_xs_.data())
{
    for(unsigned int i(height_ - Scale - Radius) ; i < height_ ; ++i)
        max_xs_ptr_[i] = max_idx_;
}


template<typename T>
template<unsigned int Radius, unsigned int Scale>
void ProjectionIDC<Radius, Scale>::project(const path::WarpPath<T> &path)
{
    assert(path.size() > 1);

    int it_min_x(-Radius);
    int it_min_y(OFFSET);
    int it_max_x(OFFSET);
    int it_max_y(-Radius-1);

    const unsigned int *path_x_ptr(path.x_ptr());
    const unsigned int *path_y_ptr(path.y_ptr());
    const unsigned int path_size(path.size());
    unsigned int last_x(path_x_ptr[0]);
    unsigned int last_y(path_y_ptr[0]);

    for(unsigned int i(1) ; i < path_size ; ++i) {
        unsigned int curr_x(path_x_ptr[i]);
        unsigned int curr_y(path_y_ptr[i]);
        bool right(curr_x > last_x);
        bool down (curr_y > last_y);

        assert(it_max_y == last_y*Scale-1-Radius);
        assert(it_max_x == last_x*Scale+1+Radius);

        if(right && down) {
            for(unsigned int i(0) ; i < Scale ; ++i) {
                ++it_min_x;
                ++it_min_y;
                ++it_max_x;
                ++it_max_y;

                updateMinXs(it_min_y, it_min_x);
                updateMaxXs(it_max_y, it_max_x - 1);
            }
        } else if(right) {
            it_min_x += Scale;
            it_max_x += Scale;
        } else if(down) {
            for(unsigned int i(0) ; i < Scale ; ++i) {
                ++it_min_y;
                ++it_max_y;
                updateMinXs(it_min_y, it_min_x);
                updateMaxXs(it_max_y, it_max_x);
            }
        }
        last_x = curr_x;
        last_y = curr_y;
    }
}

template<unsigned int Radius, unsigned int Scale>
void ProjectionIDC<Radius, Scale>::print_ascii() const
{
    for(int i = 0 ; i < height_ ; ++i) {
        for(int j = 0 ; j < min_xs_.at(i) ; ++j)
            std::cout << "# ";
        for(int j = min_xs_.at(i) ; j <= max_xs_.at(i) ; ++j)
            std::cout << "  ";
        for(int j = max_xs_.at(i) + 1 ; j < width_ ; ++j)
            std::cout << "# ";
        std::cout << std::endl;
    }
}

template<unsigned int Radius, unsigned int Scale>
void ProjectionIDC<Radius, Scale>::print() const
{
    for(int i = 0 ; i < height_ ; ++i) {
        std::cout << i << ": (" << min_xs_.at(i) << "," << max_xs_.at(i) << ")" << std::endl;
    }
}

template<unsigned int Radius, unsigned int Scale>
unsigned int ProjectionIDC<Radius, Scale>::min(const unsigned int i) const
{
    return min_xs_.at(i);
}

template<unsigned int Radius, unsigned int Scale>
unsigned int ProjectionIDC<Radius, Scale>::max(const unsigned int i) const
{
    return max_xs_.at(i);
}

template<unsigned int Radius, unsigned int Scale>
unsigned int ProjectionIDC<Radius, Scale>::size() const
{
    return height_;
}

template<unsigned int Radius, unsigned int Scale>
const unsigned int* ProjectionIDC<Radius, Scale>::maxXPtr() const  {
    return max_xs_ptr_;
}

template<unsigned int Radius, unsigned int Scale>
const unsigned int* ProjectionIDC<Radius, Scale>::minXPtr() const  {
    return min_xs_ptr_;
}

template<unsigned int Radius, unsigned int Scale>
inline void ProjectionIDC<Radius, Scale>::updateMinXs(const int y,
                        const int x)
{
    if(y > -1 && y < height_) {
        min_xs_ptr_[y] = std::max(0, std::min(x, max_idx_));
    }
}

template<unsigned int Radius, unsigned int Scale>
inline void ProjectionIDC<Radius, Scale>::updateMaxXs(const int y,
                        const int x)
{
    if(y > -1 && y < height_) {
        max_xs_ptr_[y] = std::max(0, std::min(x, max_idx_));
    }
}






#endif // PROJECTION_IDC_HPP

