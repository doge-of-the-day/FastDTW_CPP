#ifndef PATH_H
#define PATH_H

#include <utility>
#include <vector>

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
    WarpPath();

    /**
     * @brief Pushback a anchor in the path.
     * @param x     the x coordinate
     * @param y     the y coordinate
     */
    void push_back(const unsigned int x, const unsigned int y);

    /**
     * @brief operator [] can be used to get a anchor entry containing
     *        a x and a y coordinate.
     * @param i     indicator for the i-th entry
     * @return      the i-th entry of the path as a pair
     */

    std::pair<uint, uint>
    operator[] (const uint i) const;

    /**
     * @brief Return an entry in vector manner.
     * @param i     indicator fot the i-th entry
     * @return      the i-th entry of the path as a pair
     */
    std::pair<uint, uint>
    at(const uint i) const;

    /**
     * @brief Get the i-th x coordinate in the path.
     * @param i     indicator for the i-th entry
     * @return      the i-th x entry
     */
    uint x(const uint i) const;

    /**
     * @brief Get the i-th y coordinate in the path.
     * @param i     indicator for the i-th entry
     * @return      the i-th y entry
     */
    uint y(const uint i) const;
    /**
     * @brief Check wether the path is empty or not.
     * @return      true if empty
     */
    bool empty();

    void clear();

    /**
     * @brief Set the calculated distance value.
     * @param _distance     the distance to be set
     */
    void setDistance(const T _distance);

    /**
     * @brief Get the distance value of the path.
     * @return      the distance
     */
    T getDistance() const;
    /**
     * @brief Size of the path.
     * @return      size of the path
     */
    unsigned int size() const;
    /**
     * @brief Return the x data ptr for fast access.
     * @return      const ptr to the x data array / vector
     */
    const unsigned int* x_ptr() const;

    /**
     * @brief Return the y data ptr for fast access.
     * @return      const ptr to the x data array / vector
     */
    const unsigned int* y_ptr() const;
    /**
     * @brief Return the back entry of the x vector.
     * @return      the back of the x coordinates vector
     */
    unsigned int back_x();
    /**
     * @brief Return the back entry of the x vector.
     * @return      the back of the y coordinates vector
     */
    unsigned int back_y();

    /**
     * @brief Print out the coordinates of the path for debug
     *        output.
     */
    void print();

private:
    std::vector<unsigned int> anchors_x_;    /// x coordinates of a path
    std::vector<unsigned int> anchors_y_;    /// y coordinates of a path
    T                         distance_;     /// the distance
};
}
}
#endif // PATH_H

