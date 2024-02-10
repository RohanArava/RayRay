#include <iostream>
#include "./headers/myutils.h"
#include "./headers/gltf_utils.h"
#include "./headers/hittable_list.h"
#include "./headers/sphere.h"
#include "./headers/triangle.h"
#include "./headers/camera.h"
#include "./headers/material.h"
#include "./headers/bvh.h"
#include "./headers/texture.h"



void render_earth(std::ostream &out) {
    auto earth_texture = std::make_shared<image_texture>("./assets/earth.jpg");
    auto earth_surface = std::make_shared<lambertian>(earth_texture);
    auto globe = std::make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(0,0,12);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(hittable_list(globe), out);
}

void render_gltf_model(std::ostream &out, char *m_type, char *m_name)
{
    tinygltf::Model model = load_gltf_model(m_type, m_name);
    auto tris = parse_model(model);
    hittable_list world;
    auto checker = std::make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    for (int i = 0; i < tris.size(); i++)
    {
        world.add(std::make_shared<triangle>(tris[i]));
    }
    world = hittable_list(std::make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 100;
    cam.lookfrom = point3(2, -5, 0);
    cam.lookat = point3(2, 0, 0);
    cam.vup = vec3(0, 0, 1);

    cam.defocus_angle = 0;
    cam.focus_dist = 10.0;

    cam.render(world, out);
}

void render_random(std::ostream &out)
{
    hittable_list world;
    auto checker = std::make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, std::make_shared<lambertian>(checker)));

    for (int a = -3; a < 3; a++)
    {
        for (int b = -3; b < 3; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, .5), 0);
                    world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    world = hittable_list(std::make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 20;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world, out);
}

void render_textures(std::ostream &out)
{
    hittable_list world;

    auto checker = std::make_shared<checker_texture>(0.8, color(.2, .3, .1), color(.9, .9, .9));

    world.add(std::make_shared<sphere>(point3(0, -10, 0), 10, std::make_shared<lambertian>(checker)));
    world.add(std::make_shared<sphere>(point3(0, 10, 0), 10, std::make_shared<lambertian>(checker)));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world, out);
}

void print_ppm(std::ostream &out, char *m_type, char *m_name, bool isModel)
{
    if (!isModel)
    {
        const int render = 2;
        switch (render) {
            case 0:render_random(out); break;
            case 1:render_textures(out); break;
            case 2: render_earth(out); break;
        }
    }
    else
    {
        render_gltf_model(out, m_type, m_name);
    }
}