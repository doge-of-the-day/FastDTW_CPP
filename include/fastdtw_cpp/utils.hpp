#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <vector>

namespace fastdtw_cpp {
namespace utils {
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
        for(unsigned int i = 0 ; i < factor && it != end ; ++i, ++it) {
            acc += *it;
        }
        tmp[pos];
        ++pos;
    }
    dst.assign(tmp, tmp+size);
}

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
        for(unsigned int i = 0 ; i < factor && it != end ; ++i, ++it) {
            acc += *it;
        }
        tmp[pos];
        ++pos;
    }
    dst.assign(tmp, tmp+size);
}
}
}


#endif // SIGNAL_HPP
