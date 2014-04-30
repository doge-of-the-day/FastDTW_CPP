#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

int main(int argc, char *argv[])
{
    std::vector<float> test;
    for(int i = 0 ; i < 128 ; ++i)
        test.push_back(i);

    fastdtw_cpp::utils::SignalPyramid<float,2> s(test, 2);
    s.print();

    for(int i = 0 ; i < s.levelSize(0); ++i) {
        std::cout << s.levelPtr(0)[i] << std::endl;
    }

    return 0;
}

