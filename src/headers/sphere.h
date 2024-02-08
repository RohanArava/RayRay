#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray& r, interval t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto b_by_2 = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = b_by_2*b_by_2 - a*c;
        if (discriminant < 0) return false;
        
        auto sqrtd = sqrt(discriminant);
        auto root = (-b_by_2 - sqrtd) / a;
        if (!t.surrounds(root)) {
            root = (-b_by_2 + sqrtd) / a;
            if (!t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }    

    private:
        point3 center;
        double radius;
};

#endif