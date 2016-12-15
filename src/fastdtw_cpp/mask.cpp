#include <fastdtw_cpp/mask.h>

using namespace fastdtw_cpp;

Mask::Mask(const bool *_data,
     const unsigned int _size) :
    data(_data),
    size(_size)
{
}

Mask::Mask(const Mask &other) :
    data(other.data),
    size(other.size)
{
}
