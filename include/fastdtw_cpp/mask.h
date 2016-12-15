#ifndef MASK_H
#define MASK_H
namespace fastdtw_cpp {
    /**
     * @brief The Mask struct is a simple wrapper class for
     *        an array of boolean values.
     */
    struct Mask {
        Mask(const bool *_data,
             const unsigned int _size);

        Mask(const Mask &other);

        const bool        *data;
        const unsigned int size;
    };
}
#endif // MASK_H

