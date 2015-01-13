#ifndef PROJECTION_H
#define PROJECTION_H

#include <fastdtw_cpp/path.h>
#include <fastdtw_cpp/mask.h>

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
               const unsigned int _scale,
               const unsigned int _off_height = 0,
               const unsigned int _off_width = 0);

    virtual ~Projection();
    /**
     * @brief Project a warp path to the higher resolution space.
     * @param path      the path to project
     * @param radius    additional radius to enlarge projection area
     */
    template<typename T>
    void project(const path::WarpPath<T> &path,
                 const unsigned int radius = 0);

    /**
     * @brief Project a block in to the higher resolution space.
     * @param x         the block x coordinate in lower resolution space
     * @param y         the block y coordinate in lower resolution space
     * @param radius    additional radius to enlarge projection area
     */
    void block(const unsigned int x,
               const unsigned int y,
               const unsigned int radius = 0);

    /**
     * @brief Project a diagonal elemnt in the higher resoluation space.
     * @param x         lower resolution x coordinate of the anchor
     * @param y         lower resolution y coordinate of the anchor
     * @param dia_off   the diagonal offset - elements which are left out
     */
    void diagonal(const unsigned int x,
                  const unsigned int y,
                  const unsigned int dia_off = 0,
                  const unsigned int radius = 0);

    /**
     * @brief Spawn a diagonal starting element.
     * @param x         lower resolution x coordinate of the anchor
     * @param y         lower resolution y coordinate of the anchor
     * @param radius    additional radius to enlarge projection area
     */
    void diagonalStart(const unsigned int x,
                       const unsigned int y,
                       const unsigned int radius = 0);

    /**
     * @brief Return the projection value of a certaing point.
     * @param x     high resolution x coordinate
     * @param y     high resolution y coordinate
     * @return      true for projected path element
     */
    bool at(const unsigned int x, const unsigned int y) const;

    /**
     * @brief   Return the width of the projection space.
     * @return      the width of the higher resolution space
     */
    unsigned int width() const;
    /**
     * @brief   Return the height of the projection space.
     * @return      the height of the higher resolution space
     */
    unsigned int height() const;

    const Mask mask() const;

private:
    /**
     * @brief Project a corner element.
     * @param x     the higher resolution anchor x coordinate
     * @param y     the higher resolution anchor y coordinate
     */
    void corner(const unsigned int x,
                const unsigned int y,
                const unsigned int radius = 0);

    unsigned int height_;
    unsigned int width_;
    unsigned int scale_;
    bool        *data_;
};

}
}

#endif // PROJECTION_H

