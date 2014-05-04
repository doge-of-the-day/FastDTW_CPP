#include <opencv2/opencv.hpp>
#include <fastdtw_cpp/path.hpp>
#include <fastdtw_cpp/projection.hpp>

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

/// GO STRAIGHT
//void block(const unsigned int x,
//           const unsigned int y,
//           const unsigned int width,
//           const unsigned int height,
//           const unsigned int size,
//           bool *projection)
//{
//    unsigned int max_x = std::min(x + size, width);
//    unsigned int max_y = std::min(y + size, height);

//    for(unsigned int it_y = y ; it_y < max_y ; ++y) {
//        unsigned int pos = y * width;
//        for(unsigned int it_x = x ; it_x < max_x ; ++x) {
//            projection[pos + x] = true;
//        }
//    }
//}

//inline void corner(const unsigned int x,
//                   const unsigned int y,
//                   const unsigned width,
//                   const unsigned height,
//                   const unsigned size,
//                   bool *projection)
//{
//    unsigned int off = size - 1;
//    unsigned int max_x = std::min(x + off, width);
//    unsigned int max_y = std::min(y + size, height);
//    unsigned int pos_x = max_x - 1;
//    unsigned int pos_y = (max_y - 1) * width;

//    for(unsigned int it_y = y ; it_y < max_y ; ++it_y) {
//        projection[it_y * width + pos_x] = true;
//    }
//    for(unsigned int it_x = x ; it_x < max_x ; ++it_x) {
//        projection[posy + x] = true;
//    }
//}

//void diagonal(const unsigned int x,
//              const unsigned int y,
//              const unsigned size,
//              fastdtw_cpp::projection::Projection &projection)
//{
//    unsigned int max_x = std::min(x + size, width);
//    unsigned int max_y = std::min(y + size, height);

//    for(unsigned int dia = 0 ; dia < size ; ++dia) {
//        unsigned int dia_x = dia + x;
//        unsigned int dia_y = dia + y;
//        corner(dia_x, dia_y, width, height, size, projection);
//    }

//    for(unsigned int it_y = y ; it_y < max_y ; ++y) {
//        unsigned int pos = y * width;
//        for(unsigned int it_x = x ; it_x < max_x ; ++x) {
//            projection[pos + x] = true;
//        }
//    }
//}


//template<typename T>
//void project(const fastdtw_cpp::path::WarpPath &src,
//             fastdtw_cpp::path::WarpPath<T> &dst,
//             const unsigned int scale = 2,
//             const unsigned int radius = 0)
//{
//    assert(dst.empty());
//    unsigned int size = src.size();
//    unsigned int offs = scale - 1;
//    unsigned int last = size - 1;
//    unsigned int  width  = x_ptr[last] + offs;
//    unsigned int  height = y_ptr[last] + offs;
//    fastdtw_cpp::projection::Projection(height, width);
//    bool *projection_ptr = projection.data();
//    const unsigned int *x_ptr = src.x_ptr();
//    const unsigned int *y_ptr = src.y_ptr();

//    unsigned int curr_it = 0;
//    unsigned int next_it = 1;
//    while(next_it < size) {
//        unsigned int curr_x = x_ptr[curr_it];
//        unsigned int next_x = x_ptr[next_it];
//        if(next_x > curr_x) {
//            diagonal(curr_x * scale, y_ptr[curr_it] * scale,
//                     width, height, size, projection_ptr);
//        } else {
//            block(curr_x * scale, y_ptr[curr_x] * scale,
//                  width, height, scale, projection_ptr);
//        }
//        ++curr_it;
//        ++next_it;
//    }
//    block(x_ptr[next_it] * scale, y_ptr[next_it] * scale,
//          width, height, scale, projection);
//}
}


int main(int argc, char *argv[])
{
    std::vector<cv::Mat> images;
    images.push_back(cv::Mat(20,20, CV_8UC1, cv::Scalar::all(0)));
    images.push_back(cv::Mat(40,40, CV_8UC1, cv::Scalar::all(0)));
    images.push_back(cv::Mat(40,40, CV_8UC1, cv::Scalar::all(0)));

    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(0,1);
    for(unsigned int i = 2 ; i < 19 ; ++i)
        path.push_back(i-1,i);
    path.push_back(18,19);
    path.push_back(19,19);

    fastdtw_cpp::projection::Projection proj(1 + path.max_x(), 1 + path.max_y(), 2);
    unsigned int curr_it = 0;
    unsigned int next_it = 1;
    bool         was_dia = false;
    while(next_it < path.size()) {
        unsigned int curr_x = path.x(curr_it);
        unsigned int next_x = path.x(next_it);
        unsigned int curr_y = path.y(curr_it);
        unsigned int next_y = path.y(next_it);

        if(next_x > curr_x && next_y > curr_y ){
            if(was_dia)
                proj.diagonal(curr_x, curr_y);
            else {
                proj.diagonalStart(curr_x, curr_y);
                was_dia = true;
            }
        } else {
            proj.block(curr_x, curr_y);
            was_dia = false;
        }

        proj.block(next_x, next_y);

        ++curr_it;
        ++next_it;
    }



    fastdtw_cpp::path::WarpPath<float> projected_path;
    project_static<float,2>(path, projected_path);

    render(path, images.at(0), 255);
    render(projected_path, images.at(2), 255);
    for(unsigned int y = 0 ; y < proj.height() ; ++y) {
        for(unsigned int x = 0 ; x < proj.width() ; ++x) {
            images.at(1).at<uchar>(y, x) = proj.at(x,y) ? 255 : 0;
        }
    }

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
