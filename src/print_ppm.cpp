#include <iostream>
#include "./headers/myutils.h"
#include "./headers/color.h"
#include "./headers/vec3.h"

void print_ppm(std::ostream &out){

    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 0 : image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j=0; j<image_height; ++j){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i=0; i<image_width; ++i){
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            write_color(out, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}