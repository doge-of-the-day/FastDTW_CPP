#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

int main(int argc, char *argv[])
{
    std::vector<float> test;
    for(int i = 0 ; i < 127 ; ++i)
        test.push_back(i);

    fastdtw_cpp::utils::SignalPyramid<float,3> s(test, 2);
    s.print();
    return 0;
}

