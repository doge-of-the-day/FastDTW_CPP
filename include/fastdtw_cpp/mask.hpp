#ifndef MASK_HPP
#define MASK_HPP
namespace fastdtw_cpp {
    struct Mask {
        Mask(const bool *_data,
             const unsigned int _size) :
            data(_data),
            size(_size)
        {
        }

        Mask(const Mask &other) :
            data(other.data),
            size(other.size)
        {
        }

        const bool        *data;
        const unsigned int size;
    };

}
#endif // MASK_HPP
