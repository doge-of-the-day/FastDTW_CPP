#ifndef DOWNSAMLPING_HPP
#define DOWNSAMPLING_HPP


namespace fastdtw_cpp {
namespace utils {


#define FILTER_TYPE_BOX      0
#define FILTER_TYPE_BINOMIAL 1
#define FILTER_TYPE_MEDIAN   2

template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>
struct filter {
    static void perform(
        base_type* source,
        base_type* target
    );
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
struct binomial_coefficient_norm {
    static const base_type value = (
        ((base_type)binomial_coefficient<kernel_size - 1, idx>::value) *
        binomial_normalization<base_type, kernel_size>::value
    );
};


//TODO build recursive scalar product template


// ----------------------------------------------------------------

template <typename base_type, unsigned int scale, unsigned int filter_size>
//template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>
struct filter<base_type, scale, FILTER_TYPE_BINOMIAL, filter_size> {
    static inline void perform(
        base_type* source,
        base_type* target
    ) {
        *target = accu;
    }
};


// ----------------------------------------------------------------
// Median filter stuff
// ----------------------------------------------------------------



























template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>
void subsample(
    base_type* source,
    const unsigned int source_length,
    base_type* target,
    const unsigned int target_length
) {

}









} // namespace utils
} // namespace fastdtw



#endif // DOWNSAMPLING_HPP
