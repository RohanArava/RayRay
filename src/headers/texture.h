#ifndef TEXTURE_H
#define TEXTURE_H

#include "myutils.h"
#include "color.h"
#include "image_utils.h"

class texture {
  public:
    virtual ~texture() = default;

    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
  public:
    solid_color(color c) : color_value(c) {}

    solid_color(double red, double green, double blue) : solid_color(color(red,green,blue)) {}

    color value(double u, double v, const point3& p) const override {
        return color_value;
    }

  private:
    color color_value;
};

class checker_texture : public texture {
  public:
    checker_texture(double _scale, std::shared_ptr<texture> _even, std::shared_ptr<texture> _odd)
      : inv_scale(1.0 / _scale), even(_even), odd(_odd) {}

    checker_texture(double _scale, color c1, color c2)
      : inv_scale(1.0 / _scale),
        even(std::make_shared<solid_color>(c1)),
        odd(std::make_shared<solid_color>(c2))
    {}

    color value(double u, double v, const point3& p) const override {

        bool isEven;
        if(int(u)%2==0){
          if(int(v)%2==0){
            isEven = true;
          }else{
            isEven = false;
          }
        }else{
          if(int(v)%2==0){
            isEven = false;
          }else{
            isEven = true;
          }
        }

        return isEven ? even->value(u, v, p) : odd->value(u, v, p);
    }

  private:
    double inv_scale;
    std::shared_ptr<texture> even;
    std::shared_ptr<texture> odd;
};

class image_texture : public texture {
  public:
    image_texture(const char* filename) : image(filename) {}

    color value(double u, double v, const point3& p) const override {

        if (image.height() <= 0) return color(0,1,1);

        u = interval(0,1).clamp(u);
        v = 1.0 - interval(0,1).clamp(v); 

        auto i = static_cast<int>(u * image.width());
        auto j = static_cast<int>(v * image.height());
        auto pixel = image.pixel_data(i,j);

        auto color_scale = 1.0 / 255.0;
        return color(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
    }

  private:
    image image;
};

#endif