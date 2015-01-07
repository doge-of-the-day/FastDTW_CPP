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
        normed.push_back((*it + min) / range);
    }
}
}

inline void initRandom()
{
    srand (time(NULL));
}

inline float getRandom(const float prev)
{
    return (prev + (rand() % 1000 - 500) * 0.001f);
}

int main(int argc, char *argv[])
{
    int   size(1000);
    float max( 10.f);
    float min(-10.f);
    float norm(0.1f);
    std::deque<float> a(size);
    std::deque<float> b(size);

    initRandom();
    a.at(0) = 0.0f;
    b.at(0) = 0.0f;
    for(unsigned int i = 1 ; i < size ; ++i) {
        a.at(i) = std::min(max, std::max(min, getRandom(a.at(i - 1))));
        b.at(i) = std::min(max, std::max(min, getRandom(b.at(i - 1))));
    }

    int wait_time(50);

    while(true) {
        cv::Mat visual(size, size * 2, CV_8UC3, cv::Scalar::all(0));

        std::vector<float> signal_a;
        std::vector<float> signal_b;
        signal_a.assign(a.begin(), a.end());
        signal_b.assign(b.begin(), b.end());

        /// add new signal input
        a.push_back(std::min(max, std::max(min, getRandom(a.back()))));
        b.push_back(std::min(max, std::max(min, getRandom(b.back()))));
        a.pop_front();
        b.pop_front();

        fastdtw_cpp::path::WarpPath<float> p_dtw;
        fastdtw_cpp::dtw::apply(signal_a, signal_b, p_dtw);
        std::cout << " DTW : " << p_dtw.getDistance() << std::endl;

        fastdtw_cpp::path::WarpPath<float> p_fdtw;
        fastdtw_cpp::fastdtw::apply<float,40>(signal_a, signal_b, p_fdtw);
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
        cv::Mat visual_signal_a(visual, cv::Rect(size, 0, size, size * 0.5));
        cv::Mat visual_signal_b(visual, cv::Rect(size, size * 0.5, size, size * 0.5));
        cv::line(visual_signal_a, cv::Point(0, size * 0.25), cv::Point(size, size * 0.25), cv::Scalar::all(255.0));
        cv::line(visual_signal_b, cv::Point(0, size * 0.25), cv::Point(size, size * 0.25), cv::Scalar::all(255.0));

        int max_idy = visual_signal_a.rows - 1;

        for(unsigned int i = 1 ; i < size ; ++i) {
            cv::Point a1(i-1, 0.5 * max_idy - 0.5 * max_idy * norm * signal_a.at(i-1));
            cv::Point a2(i,   0.5 * max_idy - 0.5 * max_idy * norm * signal_a.at(i));;
            cv::Point b1(i-1, 0.5 * max_idy - 0.5 * max_idy * norm * signal_b.at(i-1));
            cv::Point b2(i,   0.5 * max_idy - 0.5 * max_idy * norm * signal_b.at(i));;
            cv::line(visual_signal_a, a1, a2, cv::Scalar(0,80,255));
            cv::line(visual_signal_b, b1, b2, cv::Scalar(255,255,20));
        }

//        cv::resize(visual,visual,cv::Size(1280, 640));
        cv::imshow("dtw", visual);
        int key = cv::waitKey(wait_time) & 0xFF;
        if(key == 27)
            return 0;
        if(key == 171)
            wait_time = std::max(wait_time - 10, 5);
        if(key == 173)
            wait_time = std::min(wait_time + 10, 1000);
    }

    return 0;
}

