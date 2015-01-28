#include <fastdtw_cpp/distances.h>
#include <fastdtw_cpp/distances.hpp>

namespace fastdtw_cpp {
namespace distances {

template
double def_distance<double>(const double s, const double t);

template
float def_distance<float>(const float s, const float t);

template
int def_distance<int>(const int s, const int t);
}
}
