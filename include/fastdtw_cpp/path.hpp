#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <assert.h>
#include <limits>
#include <iostream>

namespace fastdtw_cpp {
namespace path {
/**
 * @brief The WarpPath class represents a warp path through a cost matrix
 *        calculated by a dtw algorithm.
 */
template<typename T>
class WarpPath {
public:
    /// for shorter signatures
    typedef unsigned int uint;

    /**
     * @brief WarpPath constructor.
     */
    WarpPath() :
        distance_(std::numeric_limits<T>::max())
    {
    }

    /**
     * @brief Pushback a anchor in the path.
     * @param x     the x coordinate
     * @param y     the y coordinate
     */
    void push_back(const unsigned int x, const unsigned int y)
    {
        anchors_x_.push_back(x);
        anchors_y_.push_back(y);
    }

    /**
     * @brief operator [] can be used to get a anchor entry containing
     *        a x and a y coordinate.
     * @param i     indicator for the i-th entry
     * @return      the i-th entry of the path as a pair
     */
    std::pair<uint, uint>
    operator[] (const uint i) const {
        assert(i > -1);
        assert(i < anchors_x_.size());
        return std::make_pair(anchors_x_.data()[i], anchors_y_.data()[i]);
    }

    /**
     * @brief Return an entry in vector manner.
     * @param i     indicator fot the i-th entry
     * @return      the i-th entry of the path as a pair
     */
    std::pair<uint, uint>
    at(const uint i) const {
        return std::make_pair(anchors_x_.at(i), anchors_y_.at(i));
    }

    /**
     * @brief Get the i-th x coordinate in the path.
     * @param i     indicator for the i-th entry
     * @return      the i-th x entry
     */
    uint x(const uint i) const
    {
        assert(i >= 0);
        assert(i < anchors_x_.size());
        return anchors_x_.data()[i];
    }

    /**
     * @brief Get the i-th y coordinate in the path.
     * @param i     indicator for the i-th entry
     * @return      the i-th y entry
     */
    uint y(const uint i) const
    {
        assert(i >= 0);
        assert(i < anchors_y_.size());
        return anchors_y_.data()[i];
    }

    /**
     * @brief Check wether the path is empty or not.
     * @return      true if empty
     */
    bool empty()
    {
        return anchors_x_.empty() && anchors_y_.empty();
    }

    /**
     * @brief Set the calculated distance value.
     * @param _distance     the distance to be set
     */
    void setDistance(const T _distance)
    {
        distance_ = _distance;
    }

    /**
     * @brief Get the distance value of the path.
     * @return      the distance
     */
    T getDistance() const
    {
        return distance_;
    }

    /**
     * @brief Size of the path.
     * @return      size of the path
     */
    unsigned int size() const
    {
        return anchors_x_.size();
    }

    /**
     * @brief Return the x data ptr for fast access.
     * @return      const ptr to the x data array / vector
     */
    const unsigned int* const x_ptr() const
    {
        return anchors_x_.data();
    }

    /**
     * @brief Return the y data ptr for fast access.
     * @return      const ptr to the x data array / vector
     */
    const unsigned int* const y_ptr() const
    {
        return anchors_y_.data();
    }

    /**
     * @brief Return the back entry of the x vector.
     * @return      the back of the x coordinates vector
     */
    unsigned int back_x()
    {
        return anchors_x_.back();
    }

    /**
     * @brief Return the back entry of the x vector.
     * @return      the back of the y coordinates vector
     */
    unsigned int back_y()
    {
        return anchors_y_.back();
    }

    /**
     * @brief Print out the coordinates of the path for debug
     *        output.
     */
    void print()
    {
        for(unsigned int i = 0 ; i < anchors_x_.size() ; ++i) {
            std::cout << "(" << anchors_x_.at(i) << ","
                      << anchors_y_.at(i) << ")" << std::endl;

        }
    }

private:
    std::vector<unsigned int> anchors_x_;    /// x coordinates of a path
    std::vector<unsigned int> anchors_y_;    /// y coordinates of a path
    T                         distance_;     /// the distance
};
}
}
#endif // PATH_HPP
