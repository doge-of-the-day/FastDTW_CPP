#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <fastdtw_cpp/path.hpp>

namespace fastdtw_cpp {
namespace projection {

template<unsigned int Radius, unsigned int Scale>
/**
 * @brief The ProjectionIDC enables a index based projection.
 */
class ProjectionIDC {
public:
    /**
     * @brief ProjectionIDC constructor.
     * @param src_height    height of the src space
     * @param src_width     width of the src space
     */
    ProjectionIDC(const unsigned int src_height,
                const unsigned int src_width) :
        height_(src_height * Scale),
        width_(src_width * Scale),
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

    /**
     * @brief ProjectionIDC copy constructor.
     * @param other     other projection to copy
     */
    ProjectionIDC(const ProjectionIDC &other) :
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


    /**
     * @brief The project a warp path to a higher resolution path.
     * @param path  the warp path to project
     */
    template<typename T>
    inline void project(const path::WarpPath<T> &path)
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

    /**
     * @brief Print out the projection in ascii manner.
     */
    void print_ascii() const
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

    /**
     * @brief Print out the limits.
     */
    void print() const
    {
        for(int i = 0 ; i < height_ ; ++i) {
            std::cout << i << ": (" << min_xs_.at(i) << "," << max_xs_.at(i) << ")" << std::endl;
        }
    }

    /**
     * @brief Get the ith minimum index.
     * @param i     the index
     * @return      the ith minimum index
     */
    unsigned int min(const unsigned int i) const
    {
        return min_xs_.at(i);
    }

    /**
     * @brief Get the ith maximum index.
     * @param i     the index
     * @return      the ith minimum index
     */
    unsigned int max(const unsigned int i) const
    {
        return max_xs_.at(i);
    }

    /**
     * @brief The amount of index boundary indeces.
     * @return      the amount of entries
     */
    unsigned int size() const
    {
        return height_;
    }

    /**
     * @brief A pointer to the maximum index array.
     * @return      the pointer
     */
    const unsigned int* const  maxXPtr() const  {
        return max_xs_ptr_;
    }

    /**
     * @brief A pointer to the minimum index array.
     * @return      the pointer
     */
    const unsigned int* const  minXPtr() const  {
        return min_xs_ptr_;
    }


private:
    unsigned int              height_;
    unsigned int              width_;
    int                       max_idx_;
    int                       max_idy_;
    const static unsigned int OFFSET = (Scale + Radius - 1);

    std::vector<unsigned int> min_xs_;
    std::vector<unsigned int> max_xs_;
    unsigned int             *min_xs_ptr_;
    unsigned int             *max_xs_ptr_;

    inline void updateMinXs(const int y,
                            const int x)
    {
        if(y > -1 && y < height_) {
            min_xs_ptr_[y] = std::max(0, std::min(x, max_idx_));
        }
    }

    inline void updateMaxXs(const int y,
                            const int x)
    {
        if(y > -1 && y < height_) {
            max_xs_ptr_[y] = std::max(0, std::min(x, max_idx_));
        }
    }
};



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
        unsigned int anchor_x(std::max(0, (int)(x * scale_) - (int)radius));
        unsigned int anchor_y(std::max(0, (int)(y * scale_) - (int)radius));

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        unsigned int max_x(std::min(anchor_x + scale_ + radius + 1, width_));
        unsigned int max_y(std::min(anchor_y + scale_ + radius + 1, height_));

        for(unsigned int it_y(anchor_y) ; it_y < max_y ; ++it_y) {
            unsigned int pos(it_y * width_);
            for(unsigned int it_x(anchor_x) ; it_x < max_x ; ++it_x) {
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
        unsigned int anchor_x(x * scale_);
        unsigned int anchor_y(y * scale_);

        assert(anchor_x < width_);
        assert(anchor_y < height_);

        for(unsigned int dia(dia_off) ; dia < scale_ ; ++dia) {
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

    inline const std::vector<bool>& data() const
    {
        return data_;
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

        unsigned int off(scale_ - 1);
        unsigned int off_y(y + off);
        unsigned int off_x(x + off);
        unsigned int min_x(std::max(0, (int) x - (int) radius));
        unsigned int min_y(std::max(0, (int) y - (int) radius));
        unsigned int max_y(std::min(height_, y + scale_ - 1));
        unsigned int max_x(std::min(width_, x + scale_));

        if(off_x < width_)
            for(unsigned it_y(min_y) ; it_y < max_y; ++it_y)
                data_.at(it_y * width_ + off_x) = true;

        if(off_y < height_) {
            unsigned int pos(off_y * width_);
            for(unsigned it_x(min_x) ; it_x < max_x; ++it_x)
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
