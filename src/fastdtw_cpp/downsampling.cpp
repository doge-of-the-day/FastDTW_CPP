#include <fastdtw_cpp/downsampling.h>
#include <fastdtw_cpp/downsampling.hpp>

namespace fastdtw_cpp {
namespace downsampling {

template
void downSample<double, 2, FILTER_TYPE_BOX, 3>(const double* source, const unsigned int source_length, double* target);
template
void downSample<double, 2, FILTER_TYPE_BINOMIAL, 3>(const double* source, const unsigned int source_length, double* target);
template
void downSample<int, 2, FILTER_TYPE_BOX, 3>(const int* source, const unsigned int source_length, int* target);
template
void downSample<int, 2, FILTER_TYPE_BINOMIAL, 3>(const int* source, const unsigned int source_length, int* target);
template
void downSample<float, 2, FILTER_TYPE_BOX, 3>(const float* source, const unsigned int source_length, float* target);
template
void downSample<float, 2, FILTER_TYPE_BINOMIAL, 3>(const float* source, const unsigned int source_length, float* target);

}
}
