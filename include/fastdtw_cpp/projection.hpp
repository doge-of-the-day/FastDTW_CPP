#ifndef PROJECTION_HPP
#define PROJECTION_HPP

//#include <fastdtw_cpp/path.hpp>
#include <vector>
#include <assert.h>

namespace fastdtw_cpp {
namespace projection {
class Projection {
public:
    Projection(const unsigned int _height,
               const unsigned int _width,
               const unsigned int _scale) :
        height_(_height * _scale),
        width_(_width  * _scale),
        scale_(_scale),
        data_(height_ * width_, false)
    {
    }

    inline void block(const unsigned int x,
                      const unsigned int y)
    {
        unsigned int anchor_x = x * scale_;
        unsigned int anchor_y = y * scale_;

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        unsigned int max_x = std::min(anchor_x + scale_, width_);
        unsigned int max_y = std::min(anchor_y + scale_, height_);

        for(unsigned int it_y = anchor_y ; it_y < max_y ; ++it_y) {
            unsigned int pos = it_y * width_;
            for(unsigned int it_x = anchor_x ; it_x < max_x ; ++it_x) {
                data_.at(pos + it_x) = true;
            }
        }
    }


    inline void diagonal(const unsigned int x,
                         const unsigned int y,
                         const unsigned int dia_off = 0)
    {
        unsigned int anchor_x = x * scale_;
        unsigned int anchor_y = y * scale_;

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        for(unsigned int dia = dia_off ; dia < scale_ ; ++dia) {
            corner(anchor_x + dia, anchor_y + dia);
        }

    }

    inline void diagonalStart(const unsigned int x,
                              const unsigned int y)
    {
        block(x, y);
        diagonal(x, y, 1);
    }

    inline bool at(const unsigned int x, const unsigned int y) const {
        return data_.at(y * width_ + x);
    }

    inline unsigned int width() const
    {
        return width_;
    }

    inline unsigned int height() const
    {
        return height_;
    }

private:
    inline void corner(const unsigned int x,
                       const unsigned int y)
    {

        unsigned int off = scale_ - 1;
        unsigned int anchor_y = y + off;
        unsigned int anchor_x = x + off;
        unsigned int max_y = std::min(height_, y + scale_ - 1);
        unsigned int max_x = std::min(width_, x + scale_);

        if(anchor_x < width_)
            for(unsigned it_y = y ; it_y < max_y; ++it_y)
                data_.at(it_y * width_ + anchor_x) = true;

        if(anchor_y < height_) {
            unsigned int pos = anchor_y * width_;
            for(unsigned it_x = x ; it_x < max_x; ++it_x)
                data_.at(pos + it_x) = true;
        }
    }

    unsigned int height_;
    unsigned int width_;
    unsigned int scale_;
    std::vector<bool> data_;
};
}
}

#endif // PROJECTION_HPP
