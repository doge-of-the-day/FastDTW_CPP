#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "downsampling.h"

namespace fastdtw_cpp {
namespace downsampling {
/**
 * @brief Shrink any type of numerical vector by applying a shrinking factor.
 * @param src       the source vector
 * @param factor    the factor
 * @param dst       the destination vector
 */
template<typename T>
void shrink(const std::vector<T> &src, const unsigned int factor,
            std::vector<T> &dst);

/**
 * @brief Shrink any type of numerical vector by applying a shrinking factor.
 *        The factor is fixed to the value in the template.
 * @param src       the source vector
 * @param factor    the factor
 * @param dst       the destination vector
 */
template<typename T, int SCALE>
void shrink_static(const std::vector<T> &src, std::vector<T> &dst);

/**
 * @brief Calculate the offset values for a reprojection.
 * @param src_size      the original
 * @param min_size      the minimum size to reach
 * @param dst           the offset vector
 */
template <int SCALE>
void offset_vector(const unsigned int src_size,
                   const unsigned int min_size,
                   std::vector<unsigned int> &dst);

/**
 * @brief The SignalPyramid class represents a pyramid containing
 *        different shrinking levels of a signal.
 */
template<typename T, unsigned int SCALE = 2,
         unsigned int FILTER = FILTER_TYPE_BINOMIAL,
         unsigned int FILTER_SIZE = 3>
class SignalPyramid {
public:
    /// template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>

    /**
     * @brief SignalPyramid constructor.
     * @param signal        the signal to be obtained in different scales
     * @param min_size      the minumum size a level can have
     */
    SignalPyramid(const std::vector<T> &signal, const unsigned int min_size);

    /**
     * @brief This method is to print a debug output, so it can be observed, what
     *        signal data is in the pyramid at the moment.
     */
    void print();

    /**
     * @brief levelPtr
     * @param i     the level
     * @return
     */
    const T* levelPtr(const unsigned int i) const;

    /**
     * @brief Size of a given pyramid level.
     * @param i     the level
     * @return
     */
    unsigned int levelSize(const unsigned int i) const;

    std::vector<T> getLevel(const unsigned int i) const;
    /**
     * @brief The amount of levels.
     * @return
     */
    unsigned int levels() const;

private:
    std::vector<unsigned int> positions_;        /// start positions of level data
    std::vector<unsigned int> sizes_;            /// the level data sizes
    std::vector<T>            data_;             /// the data
    unsigned int             *ptr_positions_;    /// fast access pointer to positions
    unsigned int             *ptr_sizes_;        /// fast access pointer to sizes
    T                        *ptr_data_;         /// fast access pointer to data
    unsigned int              level_;

    void buildLevel(unsigned int i);
};



}
}
#endif // UTILS_H

