#include <fastdtw_cpp/fastdtw.hpp>
#include <time.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

namespace {
void normalize(const std::vector<float> &sig, const float min,
               const float max, std::vector<float> &normed)
{
    float range = max - min;
    for(std::vector<float>::const_iterator it = sig.begin() ; it != sig.end();
        ++it) {
        normed.push_back((*it - min) / range);
    }
}

void shift(const std::vector<float> &sig,
           std::vector<float> &shifted)
{
    int shift = rand() % sig.size();
    for(unsigned int i = 0 ; i < sig.size() ; ++i) {
        shifted.push_back(sig.at((i + shift) % sig.size()));
    }
}
}

int main(int argc, char *argv[])
{

    while(true) {
        int size(1024);
        cv::Mat visual(size, size * 2, CV_8UC3, cv::Scalar::all(0));

        srand (time(NULL));
        std::vector<float> signal_a;
        std::vector<float> signal_b;
        float max_a(std::numeric_limits<float>::min());
        float min_a(std::numeric_limits<float>::max());
        float prev(10.f);
        for(unsigned int i = 0 ; i < size ; ++i) {
            float a = (prev + (rand() % 1000 ) * 0.01f) / 2.f;
            max_a = std::max(a, max_a);
            min_a = std::min(a, min_a);
            signal_a.push_back(a);
            prev = a;
        }

        float max_b = max_a;
        float min_b = min_b;
        shift(signal_a, signal_b);
//        float max_b(std::numeric_limits<float>::min());
//        float min_b(std::numeric_limits<float>::max());
//        for(unsigned int i = 0 ; i < size ; ++i) {
//            float b = (rand() % 1000 ) * 0.01f;
//            max_b = std::max(b, max_b);
//            min_b = std::min(b, min_b);
//            signal_b.push_back(b);
//            signal_b.push_back(signal_a.at(i) + (10.f * (rand() % 2)));
//        }

        fastdtw_cpp::path::WarpPath<float> p_dtw;
        fastdtw_cpp::dtw::apply(signal_a, signal_b, p_dtw);
        std::cout << " DTW : " << p_dtw.getDistance() << std::endl;

        fastdtw_cpp::path::WarpPath<float> p_fdtw;
        fastdtw_cpp::fastdtw::apply<float,20>(signal_a, signal_b, p_fdtw);
        std::cout << " FTDTW : " << p_fdtw.getDistance() << std::endl;


        cv::Mat visual_dtw(visual, cv::Rect(0,0,size, size));
        for(unsigned int i = 0 ; i < p_dtw.size() ; ++i) {
            std::pair<unsigned int, unsigned int> pos = p_dtw.at(i);
            visual_dtw.at<cv::Vec3b>(pos.second, pos.first) = cv::Vec3b(255,0,0);
        }

         for(unsigned int i = 0 ; i < p_fdtw.size() ; ++i) {
            std::pair<unsigned int, unsigned int> pos = p_fdtw.at(i);
            visual_dtw.at<cv::Vec3b>(pos.second, pos.first) = cv::Vec3b(0,255,0);
        }

         //// signal and so on
        std::vector<float> norm_a;
        std::vector<float> norm_b;
        normalize(signal_a, min_a, max_a, norm_a);
        normalize(signal_b, min_b, max_b, norm_b);

        cv::Mat visual_singal(visual, cv::Rect(size, 0, size, size));
        for(unsigned int i(1) ; i < size ; ++i) {
            cv::line(visual_singal, cv::Point(i - 1, size * norm_a.at(i - 1)),
                                    cv::Point(i, size * norm_a.at(i)),
                                    cv::Scalar(0,80,255));
            cv::line(visual_singal, cv::Point(i - 1, size * norm_b.at(i - 1)),
                                    cv::Point(i, size * norm_b.at(i)),
                                    cv::Scalar(47,0,255));
        }

        cv::resize(visual,visual,cv::Size(1280, 640));
        cv::imshow("dtw", visual);
        int key = cv::waitKey(0) & 0xFF;
        if(key == 27)
            return 0;
    }

    return 0;
}

