#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

bool testProjection2() {

    /// first
    fastdtw_cpp::projection::Projection2<1,2> p(10,10);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(0,1);
    path.push_back(2,1);
    path.push_back(3,2);
    path.push_back(3,3);




    return true;
}





int main(int argc, char *argv[])
{


    fastdtw_cpp::projection::Projection2<1,2> p2 (4,4);
    fastdtw_cpp::path::WarpPath<float> w2;
    w2.push_back(0,0);
    w2.push_back(0,1);
    w2.push_back(0,2);
    w2.push_back(1,2);
    w2.push_back(2,2);
    w2.push_back(3,3);
    w2.push_back(4,4);
    w2.push_back(4,5);
    w2.push_back(5,6);
    w2.push_back(6,6);
    w2.push_back(7,6);
    w2.push_back(8,6);
    w2.push_back(8,7);
    w2.push_back(9,8);

    p2.project<float>(w2);
    p2.print();



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

