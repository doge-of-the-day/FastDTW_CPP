#ifndef MASK_H
#define MASK_H
namespace fastdtw_cpp {
    struct Mask {
        Mask(const bool *_data,
             const unsigned int _size);

        Mask(const Mask &other);

        const bool        *data;
        const unsigned int size;
    };

}
#endif // MASK_H

