#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <assert.h>

namespace fastdtw_cpp {
namespace path {
struct WarpAnchor {
    WarpAnchor(const unsigned int _x,
               const unsigned int _y) :
        x(_x),
        y(_y)
    {
    }

    unsigned int x;
    unsigned int y;
};

class WarpAnchorPath {
public:
    void push_back(const unsigned int x, const unsigned int y)
    {
        anchors.push_back(WarpAnchor(x,y));
    }

    void push_back(const WarpAnchor &anchor)
    {
        anchors.push_back(anchor);
    }

    void clear()
    {
        anchors.clear();
    }

private:
    std::vector<WarpAnchor> anchors;
};

template<typename T>
class WarpPath {
public:
    typedef unsigned int uint;

    WarpPath() :
        anchors_x(0),
        anchors_y(0),
        ptr_x(anchors_x.data()),
        ptr_y(anchors_y.data())
    {
    }

    void push_back(const unsigned int x, const unsigned int y)
    {
        anchors_x.push_back(x);
        anchors_y.push_back(y);
    }

    std::pair<uint, uint>
    operator[] (const uint i) const {
        assert(i > -1);
        assert(i < anchors_x.size());
        return std::make_pair(ptr_x[i], ptr_y[i]);
    }

    std::pair<uint, uint>
    at(const uint i) const {
        return std::make_pair(anchors_x.at(i), anchors_y.at(i));
    }

    uint
    x(const uint i) const
    {
        assert(i > -1);
        assert(i < anchors_x.size());
        return ptr_x[i];
    }

    uint
    y(const uint i) const
    {
        assert(i > -1);
        assert(i < anchors_y.size());
        return ptr_y[i];
    }

    bool empty()
    {
        return anchors_x.size() != 0 && anchors_y.size() != 0;
    }

    void setDistance(const T _distance)
    {
        distance = _distance;
    }

    T getDistance() const
    {
        return distance;
    }

    unsigned int size() const
    {
        return anchors_x.size();
    }

private:
    std::vector<unsigned int> anchors_x;
    std::vector<unsigned int> anchors_y;

    unsigned int *ptr_x;
    unsigned int *ptr_y;
    T             distance;
};
}
}
#endif // PATH_HPP
