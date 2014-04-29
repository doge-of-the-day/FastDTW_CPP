#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

void function() {
    std::vector<float> test1;
    float dist;
    fastdtw_cpp::dtw::std(test1, test1, dist);

}
