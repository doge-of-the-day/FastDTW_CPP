#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <vector>
#include <assert.h>
#include <iostream>
#include "downsampling.hpp"

namespace fastdtw_cpp {
namespace utils {
/**
 * @brief Shrink any type of numerical vector by applying a shrinking factor.
 * @param src       the source vector
 * @param factor    the factor
 * @param dst       the destination vector
 */
template<typename T>
void shrink(const std::vector<T> &src, const unsigned int factor,
            std::vector<T> &dst)
{
    unsigned int size = src.size() / factor + ((src.size() % factor) > 0 ? 1 : 0);
    T tmp[size];
    typename std::vector<T>::const_iterator it(src.begin());
    typename std::vector<T>::const_iterator end(src.end());
    unsigned int pos(0);
    while(it != end) {
        T acc(0);
        unsigned int normalize(0);
        for(unsigned int i(0) ; i < factor && it != end ; ++i, ++it) {
            acc += *it;
        }
        tmp[pos] = acc / (double) normalize;
        ++pos;
    }
    dst.assign(tmp, tmp+size);
}

/**
 * @brief Shrink any type of numerical vector by applying a shrinking factor.
 *        The factor is fixed to the value in the template.
 * @param src       the source vector
 * @param factor    the factor
 * @param dst       the destination vector
 */
template<typename T, int SCALE>
void shrink_static(const std::vector<T> &src, std::vector<T> &dst)
{
    unsigned int size(src.size() / SCALE + ((src.size() % SCALE) > 0 ? 1 : 0));
    T tmp[size];
    typename std::vector<T>::const_iterator it(src.begin());
    typename std::vector<T>::const_iterator end(src.end());
    unsigned int pos(0);
    while(it != end) {
        T acc(0);
        unsigned int normalize(0);
        for(unsigned int i(0) ; i < SCALE && it != end ; ++i, ++it) {
            acc += *it;
            ++normalize;
        }
        tmp[pos] = acc / (double) normalize;
        ++pos;
    }
    dst.assign(tmp, tmp+size);
}

/**
 * @brief Calculate the offset values for a reprojection.
 * @param src_size      the original
 * @param min_size      the minimum size to reach
 * @param dst           the offset vector
 */
template <int SCALE>
void offset_vector(const unsigned int src_size,
                   const unsigned int min_size,
                   std::vector<unsigned int> &dst)
{
    assert(min_size < src_size);
    assert(dst.empty());
    dst.push_back(0);
    unsigned int size(src_size);
    while(size / min_size > 1  /*size > min_size*/) {
        int mod = size % SCALE;
        dst.push_back(mod);
        size = size / SCALE;
    }
}

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
    SignalPyramid(const std::vector<T> &signal, const unsigned int min_size) :
        positions_(1,0),
        sizes_(1, signal.size()),
        level_(1)
    {
        unsigned int size(signal.size());
        unsigned int data_size(size);
        while(size / min_size > 1) {
            size = size / SCALE;
            data_size += size;
            positions_.push_back(positions_.back() + sizes_.back());
            sizes_.push_back(size);
            ++level_;
        }

        data_.resize(data_size);
        std::copy(signal.begin(), signal.end(), data_.begin());
        ptr_positions_ = positions_.data();
        ptr_sizes_ = sizes_.data();
        ptr_data_  = data_.data();

        for(unsigned int i = 1 ; i < level_ ; ++i) {
            buildLevel(i);
        }

    }

    /**
     * @brief This method is to print a debug output, so it can be observed, what
     *        signal data is in the pyramid at the moment.
     */
    void print()
    {
        unsigned int pos = 0;
        for(std::vector<unsigned int>::iterator it = sizes_.begin() ; it != sizes_.end() ; ++it)
        {
            for(int i = 0 ; i < *it ; ++i) {
                std::cout << " " << data_.at(pos);
                ++pos;
            }
            std::cout << std::endl;
            std::cout << " ---- " << std::endl;
        }
    }

    /**
     * @brief levelPtr
     * @param i     the level
     * @return
     */
    const T* levelPtr(const unsigned int i) const
    {
        return ptr_data_ + ptr_positions_[i];
    }

    /**
     * @brief Size of a given pyramid level.
     * @param i     the level
     * @return
     */
    unsigned int levelSize(const unsigned int i) const
    {
        return ptr_sizes_[i];
    }

    std::vector<T> getLevel(const unsigned int i) const
    {
        std::vector<T> tmp;
        T* pos = ptr_data_ + ptr_positions_[i];
        tmp.assign(pos, pos + ptr_sizes_[i]);
        return tmp;
    }

    /**
     * @brief The amount of levels.
     * @return
     */
    unsigned int levels() const
    {
        return level_;
    }



private:
    std::vector<unsigned int> positions_;        /// start positions of level data
    std::vector<unsigned int> sizes_;            /// the level data sizes
    std::vector<T>            data_;             /// the data
    unsigned int             *ptr_positions_;    /// fast access pointer to positions
    unsigned int             *ptr_sizes_;        /// fast access pointer to sizes
    T                        *ptr_data_;         /// fast access pointer to data
    unsigned int              level_;

    void buildLevel(unsigned int i)
    {
        assert(i > 0);
        T *ptr_old_entry(ptr_data_ + ptr_positions_[i-1]);
        T *ptr_new_entry(ptr_data_ + ptr_positions_[i]);
        unsigned int old_size(ptr_sizes_[i-1]);
        downSample<T, SCALE, FILTER, FILTER_SIZE>(ptr_old_entry, old_size, ptr_new_entry);
    }
};


}
}


#endif // SIGNAL_HPP
