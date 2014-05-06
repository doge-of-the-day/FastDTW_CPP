#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

int main(int argc, char *argv[])
{
    std::vector<float> test;
    std::vector<float> test2;
    for(int i = 0 ; i < 128 ; ++i) {
        test.push_back(i);
        test2.push_back(i+1);
    }


//    fastdtw_cpp::utils::SignalPyramid<float,2> s(test, 2);
//    s.print();

//    for(int i = 0 ; i < s.levelSize(0); ++i) {
//        std::cout << s.levelPtr(0)[i] << std::endl;
//    }

    fastdtw_cpp::path::WarpPath<float> path;
    float distance = 0;
    std::vector<bool> mask(128 * 128, true);
    fastdtw_cpp::dtw::apply(test, test2, mask, path);
    fastdtw_cpp::dtw::apply(test, test2, distance);
    std::cout << distance << std::endl;

    std::cout << path.getDistance() << std::endl;

    fastdtw_cpp::path::WarpPath<float> path2;
    fastdtw_cpp::fastdtw::apply(test, test2, 2, path2, 0);
    std::cout << path2.getDistance() << std::endl;

//    path.print();
//    std::cout << path.getDistance() << std::endl;
//    std::cout << " --- " << std::endl;
//    path2.print();

    return 0;
}

