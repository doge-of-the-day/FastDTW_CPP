#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>

void TEST_1_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<1,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(0,1);
    path.push_back(1,2);
    path.push_back(2,3);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 2);
    assert(p.min(1) == 0); assert(p.max(1) == 2);
    assert(p.min(2) == 0); assert(p.max(2) == 3);
    assert(p.min(3) == 0); assert(p.max(3) == 4);
    assert(p.min(4) == 0); assert(p.max(4) == 5);
    assert(p.min(5) == 0); assert(p.max(5) == 7);
    assert(p.min(6) == 1); assert(p.max(6) == 7);
    assert(p.min(7) == 2); assert(p.max(7) == 7);

    std::cout << std::endl;

}

void TEST_2_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<2,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(1,0);
    path.push_back(2,1);
    path.push_back(3,2);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 7);
    assert(p.min(1) == 0); assert(p.max(1) == 7);
    assert(p.min(2) == 0); assert(p.max(2) == 7);
    assert(p.min(3) == 0); assert(p.max(3) == 7);
    assert(p.min(4) == 1); assert(p.max(4) == 7);
    assert(p.min(5) == 2); assert(p.max(5) == 7);
    assert(p.min(6) == 3); assert(p.max(6) == 7);
    assert(p.min(7) == 4); assert(p.max(7) == 7);

    std::cout << std::endl;

}

void TEST_3_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<0,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(1,1);
    path.push_back(2,2);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 1);
    assert(p.min(1) == 0); assert(p.max(1) == 2);
    assert(p.min(2) == 1); assert(p.max(2) == 3);
    assert(p.min(3) == 2); assert(p.max(3) == 4);
    assert(p.min(4) == 3); assert(p.max(4) == 5);
    assert(p.min(5) == 4); assert(p.max(5) == 6);
    assert(p.min(6) == 5); assert(p.max(6) == 7);
    assert(p.min(7) == 6); assert(p.max(7) == 7);

    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<1,2> p1(4,4);
    p1.project<float>(path);

    p1.print_ascii();

    assert(p1.min(0) == 0); assert(p1.max(0) == 3);
    assert(p1.min(1) == 0); assert(p1.max(1) == 4);
    assert(p1.min(2) == 0); assert(p1.max(2) == 5);
    assert(p1.min(3) == 0); assert(p1.max(3) == 6);
    assert(p1.min(4) == 1); assert(p1.max(4) == 7);
    assert(p1.min(5) == 2); assert(p1.max(5) == 7);
    assert(p1.min(6) == 3); assert(p1.max(6) == 7);
    assert(p1.min(7) == 4); assert(p1.max(7) == 7);

    std::cout << std::endl;
}

void TEST_4_offsets()
{
    std::vector<unsigned int> offsets;
    fastdtw_cpp::utils::offset_vector<3>(1024, 10, offsets);
    assert(offsets.size() == 5);
    assert(offsets.at(0)  == 0);
    assert(offsets.at(1)  == 1);
    assert(offsets.at(2)  == 2);
    assert(offsets.at(3)  == 2);
    assert(offsets.at(4)  == 1);

}

void TEST_5_offsets()
{
    std::vector<unsigned int> offsets;
    fastdtw_cpp::utils::offset_vector<2>(1000, 42, offsets);
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
}

int main(int argc, char *argv[])
{

    TEST_1_projection2();
    TEST_2_projection2();
    TEST_3_projection2();
    TEST_4_offsets();

    fastdtw_cpp::projection::ProjectionIDC<1,2> p2 (9,10);
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
    p2.print_ascii();


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

