#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <vector>
#include <assert.h>
#include <iostream>

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
    typename std::vector<T>::const_iterator it = src.begin();
    typename std::vector<T>::const_iterator end = src.end();
    unsigned int pos = 0;
    while(it != end) {
        T acc = 0;
        unsigned int normalize(0);
        for(unsigned int i = 0 ; i < factor && it != end ; ++i, ++it) {
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
template<typename T, int factor>
void shrink_static(const std::vector<T> &src, std::vector<T> &dst)
{
    unsigned int size = src.size() / factor + ((src.size() % factor) > 0 ? 1 : 0);
    T tmp[size];
    typename std::vector<T>::const_iterator it = src.begin();
    typename std::vector<T>::const_iterator end = src.end();
    unsigned int pos = 0;
    while(it != end) {
        T acc = 0;
        unsigned int normalize(0);
        for(unsigned int i = 0 ; i < factor && it != end ; ++i, ++it) {
            acc += *it;
            ++normalize;
        }
        tmp[pos] = acc / (double) normalize;
        ++pos;
    }
    dst.assign(tmp, tmp+size);
}

/**
 * @brief The SignalPyramid class represents a pyramid containing
 *        different shrinking levels of a signal.
 */
template<typename T, unsigned int factor = 2>
class SignalPyramid {
public:
    /**
     * @brief SignalPyramid constructor.
     * @param signal        the signal to be obtained in different scales
     * @param min_size      the minumum size a level can have
     */
    SignalPyramid(const std::vector<T> &signal, const unsigned int min_size) :
        level(1)
    {
        positions.push_back(0);
        sizes.push_back(signal.size());

        unsigned int size(signal.size());
        unsigned int data_size(size);
        while(size > min_size) {
            size = size / factor + (size % factor > 0 ? 1 : 0);
            data_size += size;
            positions.push_back(positions.back() + sizes.back());
            sizes.push_back(size);
            ++level;
        }

        data.resize(data_size);
        std::copy(signal.begin(), signal.end(), data.begin());
        ptr_positions = positions.data();
        ptr_sizes = sizes.data();
        ptr_data  = data.data();

        for(unsigned int i = 1 ; i < level ; ++i) {
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
        for(std::vector<unsigned int>::iterator it = sizes.begin() ; it != sizes.end() ; ++it)
        {
            for(int i = 0 ; i < *it ; ++i) {
                std::cout << " " << data.at(pos);
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
    const T* const levelPtr(const unsigned int i) const
    {
        return ptr_data + ptr_positions[i];
    }

    /**
     * @brief Size of a given pyramid level.
     * @param i     the level
     * @return
     */
    unsigned int levelSize(const unsigned int i) const
    {
        return ptr_sizes[i];
    }

    /**
     * @brief The amount of levels.
     * @return
     */
    unsigned int levels() const
    {
        return level;
    }

private:
    std::vector<unsigned int> positions;        /// start positions of level data
    std::vector<unsigned int> sizes;            /// the level data sizes
    std::vector<T>            data;             /// the data
    unsigned int             *ptr_positions;    /// fast access pointer to positions
    unsigned int             *ptr_sizes;        /// fast access pointer to sizes
    T                        *ptr_data;         /// fast access pointer to data
    unsigned int              level;

    void buildLevel(unsigned int i)
    {
        assert(i > 0);
        T *ptr_old_entry = ptr_data + ptr_positions[i-1];
        T *ptr_new_entry = ptr_data + ptr_positions[i];
        unsigned int iterations = ptr_sizes[i-1];
        unsigned int it = 0;

        while(it < iterations) {
            T acc(0);
            unsigned int normalize(0);
            for(int i = 0 ; i < factor && it < iterations ; ++i,++it) {
                acc += ptr_old_entry[it];
                ++normalize;
            }
            ptr_new_entry[0] = acc / (double) normalize;
            ++ptr_new_entry;
        }
    }
};


}
}


#endif // SIGNAL_HPP
