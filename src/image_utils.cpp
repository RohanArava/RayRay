#include "./headers/image_utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/external/stb_image.h"

image::~image()
{
    if (data)
    {
        STBI_FREE(data);
    }
}

image::image(const char *filename)
{
    auto n = bytes_per_pixel;
    data = stbi_load(filename, &image_width, &image_height, &n, bytes_per_pixel);
    bytes_per_scanline = image_width * bytes_per_pixel;
    if (data == nullptr)
    {
        std::cout << "couldn't load image" << std::endl;
        exit(0);
    }
}