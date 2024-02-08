#include <iostream>
#include "./headers/myutils.h"
#include "./headers/color.h"
#include "./headers/vec3.h"

void print_ppm(std::ostream &out){

    int image_width = 256;
    int image_height = 256;
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