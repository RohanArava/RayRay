#include <iostream>
#include "./headers/myutils.h"
#include "./headers/color.h"
#include "./headers/hittable.h"
#include "./headers/hittable_list.h"
#include "./headers/sphere.h"
#include "./headers/camera.h"

void print_ppm(std::ostream &out){
    hittable_list world;

    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    // cam.out = out;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.render(world, out); 
}