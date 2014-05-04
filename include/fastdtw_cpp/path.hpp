#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <assert.h>
#include <limits>

namespace fastdtw_cpp {
namespace path {
/**
 * @brief The WarpAnchor struct represents an anchor in an warp path.
 */
struct WarpAnchor {
    /**
     * @brief WarpAnchor constructor.
     * @param _x        the x coordinate
     * @param _y        the y coordinate
     */
    WarpAnchor(const unsigned int _x,
               const unsigned int _y) :
        x(_x),
        y(_y)
    {
    }

    unsigned int x; /// the x coordinate
    unsigned int y; /// the y coordinate
};

/**
 * @brief The WarpAnchorPath class can be used as a
 *        simplier representation of a warp path.
 */
class WarpAnchorPath {
public:
    /**
     * @brief Push an anchor to the path.
     * @param x     the x coordinate
     * @param y     the y coordinate
     */
    void push_back(const unsigned int x, const unsigned int y)
    {
        anchors.push_back(WarpAnchor(x,y));
    }

    /**
     * @brief Directly push an anchor.
     * @param anchor the anchor to push
     */
    void push_back(const WarpAnchor &anchor)
    {
        anchors.push_back(anchor);
    }

    /**
     * @brief Clear the warp path.
     */
    void clear()
    {
        anchors.clear();
    }

    /**
     * @brief Get the i-th entry of the path.
     * @param i     the indicator for the i-th entry
     * @return      the i-th entry
     */
    WarpAnchor get(const unsigned int i)
    {
        return anchors.at(i);
    }

private:
    std::vector<WarpAnchor> anchors;    /// the anchors
};

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
        distance(std::numeric_limits<T>::max())
    {
    }

    /**
     * @brief Pushback a anchor in the path.
     * @param x     the x coordinate
     * @param y     the y coordinate
     */
    void push_back(const unsigned int x, const unsigned int y)
    {
        anchors_x.push_back(x);
        anchors_y.push_back(y);
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
        assert(i < anchors_x.size());
        return std::make_pair(anchors_x.data()[i], anchors_y.data()[i]);
    }

    /**
     * @brief Return an entry in vector manner.
     * @param i     indicator fot the i-th entry
     * @return      the i-th entry of the path as a pair
     */
    std::pair<uint, uint>
    at(const uint i) const {
        return std::make_pair(anchors_x.at(i), anchors_y.at(i));
    }

    /**
     * @brief Get the i-th x coordinate in the path.
     * @param i     indicator for the i-th entry
     * @return
     */
    uint x(const uint i) const
    {
        assert(i >= 0);
        assert(i < anchors_x.size());
        return anchors_x.data()[i];
    }

    /**
     * @brief Get the i-th y coordinate in the path.
     * @param i
     * @return
     */
    uint y(const uint i) const
    {
        assert(i >= 0);
        assert(i < anchors_y.size());
        return anchors_y.data()[i];
    }

    /**
     * @brief Check wether the path is empty or not.
     * @return
     */
    bool empty()
    {
        return anchors_x.empty() && anchors_y.empty();
    }

    /**
     * @brief Set the calculated distance value.
     * @param _distance     teh distance to be set
     */
    void setDistance(const T _distance)
    {
        distance = _distance;
    }

    /**
     * @brief Get the distance value of the path.
     * @return
     */
    T getDistance() const
    {
        return distance;
    }

    unsigned int size() const
    {
        return anchors_x.size();
    }

    const unsigned int* const x_ptr() const
    {
        return anchors_x.data();
    }

    const unsigned int* const y_ptr() const
    {
        return anchors_y.data();
    }

    unsigned int max_x()
    {
        return anchors_x.back();
    }

    unsigned int max_y()
    {
        return anchors_y.back();
    }

private:
    std::vector<unsigned int> anchors_x;    /// x coordinates of a path
    std::vector<unsigned int> anchors_y;    /// y coordinates of a path

//    unsigned int *ptr_x;                    /// fast access x pointer
//    unsigned int *ptr_y;                    /// fast access y pointer
    T             distance;                 /// the distance
};
}
}
#endif // PATH_HPP
