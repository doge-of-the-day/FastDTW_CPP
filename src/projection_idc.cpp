#include <fastdtw_cpp/projection_idc.h>
#include <fastdtw_cpp/projection_idc.hpp>

using namespace fastdtw_cpp;
using namespace projection;

template class
ProjectionIDC<0,2>;

template class
ProjectionIDC<1,2>;

template class
ProjectionIDC<2,2>;

template
void ProjectionIDC<0,2>::project(const path::WarpPath<int> &path);
template
void ProjectionIDC<1,2>::project(const path::WarpPath<int> &path);
template
void ProjectionIDC<2,2>::project(const path::WarpPath<int> &path);

template
void ProjectionIDC<0,2>::project(const path::WarpPath<float> &path);
template
void ProjectionIDC<1,2>::project(const path::WarpPath<float> &path);
template
void ProjectionIDC<2,2>::project(const path::WarpPath<float> &path);


template
void ProjectionIDC<0,2>::project(const path::WarpPath<double> &path);
template
void ProjectionIDC<1,2>::project(const path::WarpPath<double> &path);
template
void ProjectionIDC<2,2>::project(const path::WarpPath<double> &path);

