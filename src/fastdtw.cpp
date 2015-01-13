#include <fastdtw_cpp/fastdtw.h>
#include <fastdtw_cpp/fastdtw.hpp>

using namespace fastdtw_cpp;
using namespace fastdtw;
using namespace path;

template
void applyDyn<double>(const std::vector<double> &signal_a,
                      const std::vector<double> &signal_b,
                      const unsigned int radius,
                      WarpPath<double> &path);

template
void applyDyn<float>(const std::vector<float> &signal_a,
                     const std::vector<float> &signal_b,
                     const unsigned int radius,
                     WarpPath<float> &path);


template
void applyDyn<int>(const std::vector<int> &signal_a,
                   const std::vector<int> &signal_b,
                   const unsigned int radius,
                   WarpPath<int> &path);

