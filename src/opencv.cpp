#include <opencv2/opencv.hpp>
#include <fastdtw_cpp/path.hpp>

namespace {
void render(const fastdtw_cpp::path::WarpPath<float> &path, cv::Mat &image,
            const uchar val)
{
    assert(image.type() == CV_8UC1);
    for(unsigned int i = 0 ; i < path.size() ; ++i) {
        unsigned int x = path.x(i);
        unsigned int y = path.y(i);
        image.at<uchar>(y,x) = val;
    }
}

template<typename T, unsigned int factor>
void project_static(const fastdtw_cpp::path::WarpPath<T> &src,
                    fastdtw_cpp::path::WarpPath<T> &dst)
{
    assert(dst.empty());
    unsigned int size = src.size();
    const unsigned int *x_ptr = src.x_ptr();
    const unsigned int *y_ptr = src.y_ptr();

    for(unsigned int it = 0 ; it < size ; ++it) {
        unsigned int x = x_ptr[it] * factor;
        unsigned int y = y_ptr[it] * factor;
        for(unsigned  int i = 0 ; i < factor ; ++i) {
            unsigned int x_pro = x + i;
            for(unsigned int j = 0 ; j < factor ; ++j) {
                unsigned int y_pro = y + j;
                dst.push_back(x_pro, y_pro);
            }
        }
    }
}

template<typename T, unsigned int factor>
void project_refine(const fastdtw_cpp::path::WarpPath<T> &src,
                    fastdtw_cpp::path::WarpPath<T> &dst)
{
    assert(dst.empty());
    unsigned int size = src.size();
    const unsigned int *x_ptr = src.x_ptr();
    const unsigned int *y_ptr = src.y_ptr();

    for(unsigned int it = 0 ; it < size ; ++it) {
        unsigned int x = x_ptr[it] * factor;
        unsigned int y = y_ptr[it] * factor;
        for(unsigned  int i = 0 ; i < factor ; ++i) {
            unsigned int x_pro = x + i;
            for(unsigned int j = 0 ; j < factor ; ++j) {
                unsigned int y_pro = y + j;
                dst.push_back(x_pro, y_pro);
            }
        }
    }
}
}


int main(int argc, char *argv[])
{
    std::vector<cv::Mat> images;
    images.push_back(cv::Mat(20,20, CV_8UC1, cv::Scalar::all(0)));
    images.push_back(cv::Mat(40,40, CV_8UC1, cv::Scalar::all(0)));
    images.push_back(cv::Mat(80,80, CV_8UC1, cv::Scalar::all(0)));

    fastdtw_cpp::path::WarpPath<float> path;
    for(unsigned int i = 0 ; i < 20 ; ++i)
        path.push_back(i,i);

    /// project path
    fastdtw_cpp::path::WarpPath<float> projected_path;
    project_static<float,2>(path, projected_path);

    render(path, images.at(0), 255);
    render(projected_path, images.at(1), 255);

    cv::Mat visual;
    for(std::vector<cv::Mat>::iterator it = images.begin();
        it != images.end();
        ++it) {
        std::cout << "Next" << std::endl;
        cv::resize(*it, visual, cv::Size(200,200), 0, 0, CV_INTER_NN);
        cv::imshow("test", visual);
        cv::waitKey(0);
    }






    return 0;
}
