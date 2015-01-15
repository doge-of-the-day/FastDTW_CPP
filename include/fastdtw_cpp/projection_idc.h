#ifndef PROJECTION_IDC_H
#define PROJECTION_IDC_H

#include "path.h"

namespace fastdtw_cpp {
namespace projection {

/**
 * @brief The ProjectionIDC enables a index based projection.
 */
template<unsigned int Radius, unsigned int Scale>
class ProjectionIDC {
public:
    /**
     * @brief ProjectionIDC constructor.
     * @param src_height    height of the src space
     * @param src_width     width of the src space
     */
    ProjectionIDC(const unsigned int src_height,
                  const unsigned int src_width,
                  const unsigned int off_height = 0,
                  const unsigned int off_width = 0);

    /**
     * @brief ProjectionIDC copy constructor.
     * @param other     other projection to copy
     */
    ProjectionIDC(const ProjectionIDC &other);


    /**
     * @brief The project a warp path to a higher resolution path.
     * @param path  the warp path to project
     */
    template<typename T>
    void project(const path::WarpPath<T> &path);

    /**
     * @brief Print out the projection in ascii manner.
     */
    void print_ascii() const;

    /**
     * @brief Print out the limits.
     */
    void print() const;

    /**
     * @brief Get the ith minimum index.
     * @param i     the index
     * @return      the ith minimum index
     */
    unsigned int min(const unsigned int i) const;
    /**
     * @brief Get the ith maximum index.
     * @param i     the index
     * @return      the ith minimum index
     */
    unsigned int max(const unsigned int i) const;

    /**
     * @brief The amount of index boundary indeces.
     * @return      the amount of entries
     */
    unsigned int size() const;

    /**
     * @brief A pointer to the maximum index array.
     * @return      the pointer
     */
    const unsigned int* maxXPtr() const;
    /**
     * @brief A pointer to the minimum index array.
     * @return      the pointer
     */
    const unsigned int* minXPtr() const;


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

    void updateMinXs(const int y,
                     const int x);

    void updateMaxXs(const int y,
                     const int x);
};




}
}
#endif // PROJECTION_IDC_H

