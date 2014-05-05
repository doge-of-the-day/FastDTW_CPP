#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <fastdtw_cpp/path.hpp>

namespace fastdtw_cpp {
namespace projection {
/**
 * @brief The Projection class can be used to project a warp path
 *        into a higher resolution space.
 */
class Projection {
public:
    /**
     * @brief Projection constructor.
     * @param _height       height of the lower resolution space
     * @param _width        width of the lower resolution space
     * @param _scale        the upscale of the lower resolution
     */
    Projection(const unsigned int _height,
               const unsigned int _width,
               const unsigned int _scale) :
        height_(_height * _scale),
        width_(_width  * _scale),
        scale_(_scale),
        data_(height_ * width_, false)
    {
    }

    /**
     * @brief Project a warp path to the higher resolution space.
     * @param path      the path to project
     * @param radius    additional radius to enlarge projection area
     */
    template<typename T>
    inline void project(const path::WarpPath<T> &path,
                        const unsigned int radius = 0)
    {
        unsigned int curr_it = 0;
        unsigned int next_it = 1;
        bool         was_dia = false;
        const unsigned int *x_ptr = path.x_ptr();
        const unsigned int *y_ptr = path.y_ptr();

        while(next_it < path.size()) {
            unsigned int curr_x = x_ptr[curr_it];
            unsigned int next_x = x_ptr[next_it];
            unsigned int curr_y = y_ptr[curr_it];
            unsigned int next_y = y_ptr[next_it];

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
        unsigned int last = path.size() - 1;
        block(x_ptr[last], y_ptr[last], radius);
    }

    /**
     * @brief Project a block in to the higher resolution space.
     * @param x         the block x coordinate in lower resolution space
     * @param y         the block y coordinate in lower resolution space
     * @param radius    additional radius to enlarge projection area
     */
    inline void block(const unsigned int x,
                      const unsigned int y,
                      const unsigned int radius = 0)
    {
        unsigned int anchor_x = std::max(0, (int)(x * scale_) - (int)radius);
        unsigned int anchor_y = std::max(0, (int)(y * scale_) - (int)radius);

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        unsigned int max_x = std::min(anchor_x + scale_ + radius, width_);
        unsigned int max_y = std::min(anchor_y + scale_ + radius, height_);

        for(unsigned int it_y = anchor_y ; it_y < max_y ; ++it_y) {
            unsigned int pos = it_y * width_;
            for(unsigned int it_x = anchor_x ; it_x < max_x ; ++it_x) {
                data_.at(pos + it_x) = true;
            }
        }
    }

    /**
     * @brief Project a diagonal elemnt in the higher resoluation space.
     * @param x         lower resolution x coordinate of the anchor
     * @param y         lower resolution y coordinate of the anchor
     * @param dia_off   the diagonal offset - elements which are left out
     */
    inline void diagonal(const unsigned int x,
                         const unsigned int y,
                         const unsigned int dia_off = 0,
                         const unsigned int radius = 0)
    {
        unsigned int anchor_x = x * scale_;
        unsigned int anchor_y = y * scale_;

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        for(unsigned int dia = dia_off ; dia < scale_ ; ++dia) {
            corner(anchor_x + dia, anchor_y + dia, radius);
        }

    }

    /**
     * @brief Spawn a diagonal starting element.
     * @param x         lower resolution x coordinate of the anchor
     * @param y         lower resolution y coordinate of the anchor
     * @param radius    additional radius to enlarge projection area
     */
    inline void diagonalStart(const unsigned int x,
                              const unsigned int y,
                              const unsigned int radius = 0)
    {
        block(x, y, radius);
        diagonal(x, y, 1);
    }

    /**
     * @brief Return the projection value of a certaing point.
     * @param x     high resolution x coordinate
     * @param y     high resolution y coordinate
     * @return      true for projected path element
     */
    inline bool at(const unsigned int x, const unsigned int y) const {
        return data_.at(y * width_ + x);
    }

    /**
     * @brief   Return the width of the projection space.
     * @return      the width of the higher resolution space
     */
    inline unsigned int width() const
    {
        return width_;
    }

    /**
     * @brief   Return the height of the projection space.
     * @return      the height of the higher resolution space
     */
    inline unsigned int height() const
    {
        return height_;
    }

private:
    /**
     * @brief Project a corner element.
     * @param x     the higher resolution anchor x coordinate
     * @param y     the higher resolution anchor y coordinate
     */
    inline void corner(const unsigned int x,
                       const unsigned int y,
                       const unsigned int radius = 0)
    {

        unsigned int off   = scale_ - 1;
        unsigned int off_y = y + off;
        unsigned int off_x = x + off;
        unsigned int min_x = std::max(0, (int) x - (int) radius);
        unsigned int min_y = std::max(0, (int) y - (int) radius);
        unsigned int max_y = std::min(height_, y + scale_ - 1);
        unsigned int max_x = std::min(width_, x + scale_);

        if(off_x < width_)
            for(unsigned it_y = min_y ; it_y < max_y; ++it_y)
                data_.at(it_y * width_ + off_x) = true;

        if(off_y < height_) {
            unsigned int pos = off_y * width_;
            for(unsigned it_x = min_x ; it_x < max_x; ++it_x)
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
