#ifndef DOWNSAMLPING_HPP
#define DOWNSAMPLING_HPP


namespace fastdtw_cpp {
namespace utils {


#define FILTER_TYPE_BOX      0
#define FILTER_TYPE_BINOMIAL 1

template <typename base_type, unsigned int filter_type, unsigned int filter_size>
struct filter {
    static const base_type perform(
        const base_type* source
    );
};

// ----------------------------------------------------------------
// Box filter stuff
// ----------------------------------------------------------------

template <typename base_type, unsigned int n>
struct normalization {
    static const base_type value = ((base_type)1.0) / ((base_type)n);
};


template <typename base_type, unsigned int n>
struct mean_helper {
    static inline const base_type perform(
        const base_type* source
    ) {
        return (*source) + mean_helper<base_type, n - 1>::perform(source + 1);
    }
};

template <typename base_type>
struct mean_helper<base_type, 1> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return (*source);
    }
};

template <typename base_type>
struct mean_helper<base_type, 0> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return base_type();
    }
};

template <typename base_type, unsigned int n>
struct mean {
    static inline const base_type perform(
        const base_type* source
    ) {
        return (
            mean_helper<base_type, n>::perform(source) *
            normalization<base_type, n>::value
        );
    }
};

template <typename base_type, unsigned int filter_size>
struct filter<base_type, FILTER_TYPE_BOX, filter_size> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return mean<base_type, filter_size>::perform(source);
    }
};



// ----------------------------------------------------------------
// Kernel stuff
// ----------------------------------------------------------------

template <typename base_type, unsigned int n>
struct dot_helper {
    static inline const base_type perform(
        const base_type* source,
        const base_type* source2
    ) {
        return (
            ((*source) * (*source2)) +
            dot_helper<base_type, n - 1>::perform(source + 1, source2 + 1)
        );
    }
};

template <typename base_type>
struct dot_helper<base_type, 1> {
    static inline const base_type perform(
        const base_type* source,
        const base_type* source2
    ) {
        return (*source) * (*source2);
    }
};

template <typename base_type>
struct dot_helper<base_type, 0> {
    static inline const base_type perform(
        const base_type* source,
        const base_type* source2
    ) {
        return base_type();
    }
};

template <typename base_type, unsigned int n>
struct dot {
    static inline const base_type perform(
        const base_type* source,
        const base_type* source2
    ) {
        return dot_helper<base_type, n>::perform(source, source2);
    }
};




template <
    typename base_type,
    unsigned int n,
    unsigned int n_max,
    template <typename, unsigned int, unsigned int> class kernel
>
struct dot_kernel_helper {
    static inline const base_type perform(
        const base_type* source
    ) {
        return (
            (*source) *
            kernel<base_type, n_max, n_max - n>::value
        ) + dot_kernel_helper<base_type, n - 1, n_max, kernel>::perform(source + 1);
    }
};


template <
    typename base_type,
    unsigned int n_max,
    template <typename, unsigned int, unsigned int> class kernel
>
struct dot_kernel_helper<base_type, 1, n_max, kernel> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return (
            (*source) *
            kernel<base_type, n_max, n_max - 1>::value
        );
    }
};


template <
    typename base_type,
    unsigned int n_max,
    template <typename, unsigned int, unsigned int> class kernel
>
struct dot_kernel_helper<base_type, 0, n_max, kernel> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return base_type();
    }
};


template <
    typename base_type,
    unsigned int n,
    template <typename, unsigned int, unsigned int> class kernel
>
struct dot_kernel {
    static inline const base_type peform(
        const base_type* source
    ) {
        return dot_kernel_helper<base_type, n, n, kernel>::perform(source);
    }
};



// ----------------------------------------------------------------
// Binomial filter stuff
// ----------------------------------------------------------------

template <unsigned int arg>
struct factorial {
    enum { value =  factorial<arg - 1>::value };
};


template <> struct factorial<0> { enum { value = 1}; };
template <> struct factorial<1> { enum { value = 1}; };
template <> struct factorial<2> { enum { value = 2}; };
template <> struct factorial<3> { enum { value = 6}; };
template <> struct factorial<4> { enum { value = 24}; };
template <> struct factorial<5> { enum { value = 120}; };
template <> struct factorial<6> { enum { value = 720}; };
template <> struct factorial<7> { enum { value = 5040}; };
template <> struct factorial<8> { enum { value = 40320}; };

template <unsigned int n, unsigned int k>
struct binomial_coefficient {
    enum { value = factorial<n>::value / (factorial<k>::value * factorial<n - k>::value) };
};


template <typename base_type, unsigned int kernel_size>
struct binomial_normalization {
    static const base_type value = ((base_type)1.0) / ((base_type)(0x1 << (kernel_size - 1)));
};


template <typename base_type, unsigned int kernel_size, unsigned int idx>
struct binomial_kernel {
    static const base_type value = (
        ((base_type)binomial_coefficient<kernel_size - 1, idx>::value) *
        binomial_normalization<base_type, kernel_size>::value
    );
};

template <typename base_type, unsigned int filter_size>
struct filter<base_type, FILTER_TYPE_BINOMIAL, filter_size> {
    static inline const base_type perform(
        const base_type* source
    ) {
        return dot_kernel<base_type, filter_size, binomial_kernel>::peform(source);
    }
};




// ----------------------------------------------------------------
// Downsampling stuff
// ----------------------------------------------------------------

template <unsigned int filter_size>
struct filter_bounds {
    enum { center = (filter_size - 1) / 2};
    enum { left   = center };
    enum { right  = filter_size - (center + 1) };
};



template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>
void downSample(
    const base_type* source,
    const unsigned int source_length,
    base_type* target
) {
    //
    const unsigned int target_length = source_length / scale;
    base_type buffer[filter_size];
    //
    // compute important boundary information.
    //
    int j = 0;
    const int i_min = 0;
    const int i_lbd = (int)std::ceil(
        (double)(filter_bounds<filter_size>::left) /
        (double)(scale)
    );
    const int i_ubd = std::max(i_lbd - 1, (int)(target_length) - (1 + i_lbd));
    const int i_max = target_length - 1;
    //
    // convole left region (boundary-safe)
    //
    for (int i = i_min; i < i_lbd; i++) {
        //
        for (int k = 0; k < filter_size; k++) {
            register int idx = k + j - filter_bounds<filter_size>::left;
            if (idx < 0) idx = 0;
            if (idx >= source_length) idx = source_length - 1;
            buffer[k] = source[idx];
        }
        //
        target[i] = filter<base_type, filter_type, filter_size>::perform(
            buffer
        );
        //
        j += scale;
    }
    //
    // convole inner region
    //
    for (int i = i_lbd; i <= i_ubd; i++) {
        target[i] = filter<base_type, filter_type, filter_size>::perform(
            source + j - filter_bounds<filter_size>::left
        );
        j += scale;
    }
    //
    // colvole right region (boundary-safe)
    //
    for (int i = i_ubd + 1; i <= i_max; i++) {
        //
        for (int k = 0; k < filter_size; k++) {
            register int idx = k + j - filter_bounds<filter_size>::left;
            if (idx < 0) idx = 0;
            if (idx >= source_length) idx = source_length - 1;
            buffer[k] = source[idx];
        }
        //
        target[i] = filter<base_type, filter_type, filter_size>::perform(
            buffer
        );
        //
        j += scale;
    }
}






} // namespace utils
} // namespace fastdtw



#endif // DOWNSAMPLING_HPP
