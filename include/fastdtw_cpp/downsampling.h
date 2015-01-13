#ifndef DOWNSAMPLING_H
#define DOWNSAMPLING_H

namespace fastdtw_cpp {
namespace downsampling {

#define FILTER_TYPE_BOX      0
#define FILTER_TYPE_BINOMIAL 1

template <typename base_type, unsigned int scale, unsigned int filter_type, unsigned int filter_size>
void downSample(const              base_type* source,
                const unsigned int source_length,
                base_type*         target);
}
}

#endif // DOWNSAMPLING_H

