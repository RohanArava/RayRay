#ifndef _IMAGEUTILS_H_
#define _IMAGEUTILS_H_

#include <cstdlib>
#include <iostream>

class image
{
public:
    virtual ~image();
    image() : data(nullptr) {}
    image(const char *filename);
    int width() const { return (data == nullptr) ? 0 : image_width; }
    int height() const { return (data == nullptr) ? 0 : image_height; }
    const unsigned char *pixel_data(int x, int y) const
    {
        static unsigned char magenta[] = {255, 0, 255};
        if (data == nullptr)
            return magenta;

        x = clamp(x, 0, image_width);
        y = clamp(y, 0, image_height);

        return data + y * bytes_per_scanline + x * bytes_per_pixel;
    }

private:
    const int bytes_per_pixel = 3;
    unsigned char *data;
    int image_width, image_height;
    int bytes_per_scanline;

    static int clamp(int x, int low, int high)
    {
        if (x < low)
            return low;
        if (x < high)
            return x;
        return high - 1;
    }
};

#endif