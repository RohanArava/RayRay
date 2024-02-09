#include <iostream>
#include "./headers/myutils.h"
#include "./headers/hittable_list.h"
#include "./headers/sphere.h"
#include "./headers/triangle.h"
#include "./headers/camera.h"
#include "./headers/material.h"

void print_ppm(std::ostream &out){
    hittable_list world;

    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<dielectric>(1.5);
    auto material_triangle = std::make_shared<metal>(color(0.9, 0, 0.7), 0.2);

    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.0), point3( 0.4,    0.4, -1.4),   0.5, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(std::make_shared<quadrilateral>(point3(0.7, 1 ,-1.5), point3(0.7, 0 ,-1.5), point3(0.7, 0 ,1.5), point3(0.7, 1, 1.5), material_triangle));
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 32;
    cam.max_depth = 10;
    cam.vfov = 45;
    cam.lookfrom = point3(-4, 3, -1);
    cam.lookat   = point3(0.7, 0.3, -1);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;
    cam.focus_dist = 3.4;
    cam.render(world, out); 
}