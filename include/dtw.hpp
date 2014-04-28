#ifndef DTW_HPP
#define DTW_HPP
#include <vector>
#include <limits>
#include <complex>
#include <assert.h>

#include <opencv2/opencv.hpp>

//// http://en.wikipedia.org/wiki/Dynamic_time_warping

namespace dtw {
template<typename T>
struct def_distance {
    T operator ()(const T s, const T t) const
    {
        return std::abs(s - t);
    }
};


struct dtw {
    static void std(const std::vector<float> &signal_a, const std::vector<float> &signal_b,
                    float &distance)
    {
        assert(signal_a.size() != 0);
        assert(signal_b.size() != 0);
        /// signal_a is rows
        /// signal_b is cols
        unsigned int rows = signal_a.size() + 1;
        unsigned int cols = signal_b.size() + 1;
        std::vector<float> distances;
        distances.resize(rows * cols, 0.f);

        float *dist_ptr = distances.data();
        for(unsigned int i = 1 ; i < rows ; ++i)
            dist_ptr[i * cols] = std::numeric_limits<float>::infinity();
        for(unsigned int j = 1 ; j < cols ; ++j)
            dist_ptr[j] = std::numeric_limits<float>::infinity();

        dist_ptr[0] = 0.f;

        const float *siga_ptr = signal_a.data();
        const float *sigb_ptr = signal_b.data();
        def_distance<float> d;

        for(unsigned int i = 1 ; i < rows ; ++i) {
            for(unsigned int j = 1 ; j < cols ; ++j) {
                float cost = d(siga_ptr[i], sigb_ptr[j]);
                float insertion = dist_ptr[(i - 1) * cols + j];
                float deletion  = dist_ptr[ i * cols + j - 1];
                float match     = dist_ptr[(i - 1) * cols + j - 1];
                dist_ptr[i * cols + j] = cost + std::min(insertion, std::min(deletion, match));
            }
        }

        distance = dist_ptr[rows * cols - 1];
    }

    static void arr(const std::vector<float> &signal_a, const std::vector<float> &signal_b,
                    float &distance)
    {
        assert(signal_a.size() != 0);
        assert(signal_b.size() != 0);
        /// signal_a is rows
        /// signal_b is cols
        unsigned int rows = signal_a.size() + 1;
        unsigned int cols = signal_b.size() + 1;
        float distances[rows * cols];

        for(unsigned int i = 1 ; i < rows ; ++i)
            distances[i * cols] = std::numeric_limits<float>::infinity();
        for(unsigned int j = 1 ; j < cols ; ++j)
            distances[j] = std::numeric_limits<float>::infinity();

        distances[0] = 0.f;

        const float *siga_ptr = signal_a.data();
        const float *sigb_ptr = signal_b.data();
        def_distance<float> d;

        for(unsigned int i = 1 ; i < rows ; ++i) {
            int i1((i - 1) * cols);

            for(unsigned int j = 1 ; j < cols ; ++j) {
                int j1(j - 1);
                float cost(d(siga_ptr[i], sigb_ptr[j]));
                float insertion(distances[i1  + j]);

                float deletion( distances[i1 + cols + j1]);
                float match(distances[i1 + j1]);
                distances[i1 + cols + j] = cost + std::min(insertion, std::min(deletion, match));
            }
        }

        distance = distances[rows * cols - 1];
    }

    static void loc(const std::vector<float> &signal_a, const std::vector<float> &signal_b,
                    const int adapt_window, float &distance) {
        assert(signal_a.size() != 0);
        assert(signal_b.size() != 0);
        /// signal_a is rows
        /// signal_b is cols
        int rows = signal_a.size() + 1;
        int cols = signal_b.size() + 1;
        std::vector<float> distances;
        distances.resize(rows * cols, std::numeric_limits<float>::infinity());

        float *dist_ptr = distances.data();
        dist_ptr[0] = 0.f;

        int w = std::max(adapt_window, (const int) std::abs(cols - rows));

        const float *siga_ptr = signal_a.data();
        const float *sigb_ptr = signal_b.data();
        def_distance<float> d;

        for(int i = 1 ; i < rows ; ++i) {
            for(int j = std::max(1, i - w) ; j < std::min(cols, i + w + 1); ++j) {
                float cost = d(siga_ptr[i], sigb_ptr[j]);
                float insertion = dist_ptr[(i - 1) * cols + j];
                float deletion  = dist_ptr[ i * cols + j - 1];
                float match     = dist_ptr[(i - 1) * cols + j - 1];
                dist_ptr[i * cols + j] = cost + std::min(insertion, std::min(deletion, match));
            }
        }

        distance = dist_ptr[rows * cols - 1];
    }


};
}
#endif // DTW_HPP
