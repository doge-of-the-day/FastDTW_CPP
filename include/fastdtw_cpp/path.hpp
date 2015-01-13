#ifndef PATH_HPP
#define PATH_HPP

#include "path.h"

#include <assert.h>
#include <limits>
#include <iostream>

namespace fastdtw_cpp {
namespace path {

template<typename T>
WarpPath<T>::WarpPath() :
    distance_(std::numeric_limits<T>::max())
{
}

template<typename T>
void WarpPath<T>::push_back(const unsigned int x, const unsigned int y)
{
    anchors_x_.push_back(x);
    anchors_y_.push_back(y);
}

template<typename T>
std::pair<uint, uint>
WarpPath<T>::operator[] (const uint i) const {
    assert(i > -1);
    assert(i < anchors_x_.size());
    return std::make_pair(anchors_x_.data()[i], anchors_y_.data()[i]);
}

template<typename T>
std::pair<uint, uint>
WarpPath<T>::at(const uint i) const {
    return std::make_pair(anchors_x_.at(i), anchors_y_.at(i));
}

template<typename T>
uint WarpPath<T>::x(const uint i) const
{
    assert(i >= 0);
    assert(i < anchors_x_.size());
    return anchors_x_.data()[i];
}

template<typename T>
uint WarpPath<T>::y(const uint i) const
{
    assert(i >= 0);
    assert(i < anchors_y_.size());
    return anchors_y_.data()[i];
}

template<typename T>
bool WarpPath<T>::empty()
{
    return anchors_x_.empty() && anchors_y_.empty();
}

template<typename T>
void WarpPath<T>::clear()
{
    anchors_x_.clear();
    anchors_y_.clear();
    distance_ = std::numeric_limits<T>::max();
}


template<typename T>
void WarpPath<T>::setDistance(const T _distance)
{
    distance_ = _distance;
}

template<typename T>
T WarpPath<T>::getDistance() const
{
    return distance_;
}

template<typename T>
unsigned int WarpPath<T>::size() const
{
    return anchors_x_.size();
}

template<typename T>
const unsigned int* WarpPath<T>::x_ptr() const
{
    return anchors_x_.data();
}

template<typename T>
const unsigned int* WarpPath<T>::y_ptr() const
{
    return anchors_y_.data();
}

template<typename T>
unsigned int WarpPath<T>::back_x()
{
    return anchors_x_.back();
}

template<typename T>
unsigned int WarpPath<T>::back_y()
{
    return anchors_y_.back();
}

template<typename T>
void WarpPath<T>::print()
{
    for(unsigned int i = 0 ; i < anchors_x_.size() ; ++i) {
        std::cout << "(" << anchors_x_.at(i) << ","
                  << anchors_y_.at(i) << ")" << std::endl;

    }
}
}
}
#endif // PATH_HPP
