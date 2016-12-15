#include <fastdtw_cpp/projection.h>
#include <fastdtw_cpp/projection.hpp>

#include <assert.h>


using namespace fastdtw_cpp;
using namespace projection;

Projection::Projection(const unsigned int _height,
                       const unsigned int _width,
                       const unsigned int _scale,
                       const unsigned int _off_height,
                       const unsigned int _off_width) :
    height_(_height * _scale + _off_height),
    width_(_width  * _scale + _off_width),
    scale_(_scale)
{
    data_ = new bool [height_ * width_];
    std::fill(data_, data_ + height_ * width_, false);
}

Projection::~Projection()
{
   delete[] data_;
}

template
void Projection::project<double>(const path::WarpPath<double> &path,
                                 const unsigned int radius);
template
void Projection::project<float>(const path::WarpPath<float> &path,
                                const unsigned int radius);
template
void Projection::project<int>(const path::WarpPath<int> &path,
                              const unsigned int radius);


void Projection::block(const unsigned int x,
                       const unsigned int y,
                       const unsigned int radius)
{
    unsigned int anchor_x(std::max(0, (int)(x * scale_) - (int)radius));
    unsigned int anchor_y(std::max(0, (int)(y * scale_) - (int)radius));

    assert(anchor_x < width_);
    assert(anchor_y < height_);

    unsigned int max_x(std::min(anchor_x + scale_ + radius + 1, width_));
    unsigned int max_y(std::min(anchor_y + scale_ + radius + 1, height_));

    for(unsigned int it_y(anchor_y) ; it_y < max_y ; ++it_y) {
        unsigned int pos(it_y * width_);
        for(unsigned int it_x(anchor_x) ; it_x < max_x ; ++it_x) {
            data_[pos + it_x] = true;
        }
    }
}

void Projection::diagonal(const unsigned int x,
                          const unsigned int y,
                          const unsigned int dia_off,
                          const unsigned int radius)
{
    unsigned int anchor_x(x * scale_);
    unsigned int anchor_y(y * scale_);

    assert(anchor_x < width_);
    assert(anchor_y < height_);

    for(unsigned int dia(dia_off) ; dia < scale_ ; ++dia) {
        corner(anchor_x + dia, anchor_y + dia, radius);
    }

}

void Projection::diagonalStart(const unsigned int x,
                               const unsigned int y,
                               const unsigned int radius)
{
    block(x, y, radius);
    diagonal(x, y, 1);
}

bool Projection::at(const unsigned int x, const unsigned int y) const
{
    return data_[y * width_ + x];
}

unsigned int Projection::width() const
{
    return width_;
}

unsigned int Projection::height() const
{
    return height_;
}

const Mask Projection::mask() const
{
    return Mask(data_, width_ * height_);
}

void Projection::corner(const unsigned int x,
                        const unsigned int y,
                        const unsigned int radius)
{

    unsigned int off(scale_ - 1);
    unsigned int off_y(y + off);
    unsigned int off_x(x + off);
    unsigned int min_x(std::max(0, (int) x - (int) radius));
    unsigned int min_y(std::max(0, (int) y - (int) radius));
    unsigned int max_y(std::min(height_, y + scale_ - 1));
    unsigned int max_x(std::min(width_, x + scale_));

    if(off_x < width_)
        for(unsigned it_y(min_y) ; it_y < max_y; ++it_y) {
            data_[it_y * width_ + off_x] = true;
        }

    if(off_y < height_) {
        unsigned int pos(off_y * width_);
        for(unsigned it_x(min_x) ; it_x < max_x; ++it_x)
            data_[pos + it_x] = true;
    }
}
