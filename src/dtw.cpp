#include <fastdtw_cpp/dtw.h>
#include <fastdtw_cpp/dtw.hpp>

using namespace fastdtw_cpp;
using namespace dtw;
using namespace path;

template
void trace<double>(const double            *data,
                   const unsigned int       rows,
                   const unsigned int       cols,
                   WarpPath<double>  &path);

template
void trace<float>(const float             *data,
                  const unsigned int       rows,
                  const unsigned int       cols,
                  path::WarpPath<float>   &path);

template
void trace<int>(const int               *data,
                const unsigned int       rows,
                const unsigned int       cols,
                path::WarpPath<int>     &path);

template
void apply<double>(const std::vector<double> &signal_a,
                   const std::vector<double> &signal_b,
                   double &distance);

template
void apply<float>(const std::vector<float> &signal_a,
                  const std::vector<float> &signal_b,
                  float &distance);

template
void apply<int>(const std::vector<int> &signal_a,
                const std::vector<int> &signal_b,
                int &distance);

template
void apply<double>(const std::vector<double> &signal_a,
                   const std::vector<double> &signal_b,
                   path::WarpPath<double>    &path);

template
void apply<float>(const std::vector<float> &signal_a,
                  const std::vector<float> &signal_b,
                  path::WarpPath<float>    &path);

template
void apply<int>(const std::vector<int> &signal_a,
                const std::vector<int> &signal_b,
                path::WarpPath<int>    &path);

template
void apply<double>(const double* signal_a, const unsigned int size_a,
                   const double* signal_b, const unsigned int size_b,
                   path::WarpPath<double> &path);

template
void apply<float>(const float* signal_a, const unsigned int size_a,
                  const float* signal_b, const unsigned int size_b,
                  path::WarpPath<float> &path);

template
void apply<int>(const int* signal_a, const unsigned int size_a,
                const int* signal_b, const unsigned int size_b,
                path::WarpPath<int> &path);

template
void apply<double>(const double* signal_a, const unsigned int size_a,
                   const double* signal_b, const unsigned int size_b,
                   const Mask &mask,
                   path::WarpPath<double> &path);

template
void apply<float>(const float* signal_a, const unsigned int size_a,
                  const float* signal_b, const unsigned int size_b,
                  const Mask &mask,
                  path::WarpPath<float> &path);

template
void apply<int>(const int* signal_a, const unsigned int size_a,
                const int* signal_b, const unsigned int size_b,
                const Mask &mask,
                path::WarpPath<int> &path);

template
void apply<double>(const std::vector<double>    &signal_a,
                   const std::vector<double>    &signal_b,
                   const Mask              &mask,
                   path::WarpPath<double>       &path);

template
void apply<float>(const std::vector<float>    &signal_a,
                  const std::vector<float>    &signal_b,
                  const Mask              &mask,
                  path::WarpPath<float>       &path);

template
void apply<int>(const std::vector<int>    &signal_a,
                const std::vector<int>    &signal_b,
                const Mask              &mask,
                path::WarpPath<int>       &path);


template
void apply<double>(const double* signal_a, const unsigned int size_a,
                   const double* signal_b, const unsigned int size_b,
                   const unsigned int* min_xs,
                   const unsigned int* max_xs,
                   const unsigned int  indeces,
                   path::WarpPath<double> &path);

template
void apply<float>(const float* signal_a, const unsigned int size_a,
                  const float* signal_b, const unsigned int size_b,
                  const unsigned int* min_xs,
                  const unsigned int* max_xs,
                  const unsigned int  indeces,
                  path::WarpPath<float> &path);

template
void apply<int>(const int* signal_a, const unsigned int size_a,
                const int* signal_b, const unsigned int size_b,
                const unsigned int* min_xs,
                const unsigned int* max_xs,
                const unsigned int  indeces,
                path::WarpPath<int> &path);
