#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(point3 _center, double _radius, std::shared_ptr<material> _material) : center1(_center), radius(_radius), mat(_material), is_moving(false)
    {
        auto rvec = vec3(radius, radius, radius);
        bbox = aabb(center1 - rvec, center1 + rvec);
    }

    sphere(point3 _center1, point3 _center2, double _radius, std::shared_ptr<material> _material)
        : center1(_center1), radius(_radius), mat(_material), is_moving(true)
    {
        auto rvec = vec3(radius, radius, radius);
        aabb box1(_center1 - rvec, _center1 + rvec);
        aabb box2(_center2 - rvec, _center2 + rvec);
        bbox = aabb(box1, box2);
        center_vec = _center2 - _center1;
    }

    bool hit(const ray &r, interval t, hit_record &rec) const override
    {
        point3 center_h = is_moving ? center(r.time()) : center1;
        vec3 oc = r.origin() - center_h;
        auto a = r.direction().length_squared();
        auto b_by_2 = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = b_by_2 * b_by_2 - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);
        auto root = (-b_by_2 - sqrtd) / a;
        if (!t.surrounds(root))
        {
            root = (-b_by_2 + sqrtd) / a;
            if (!t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center_h) / radius;
        rec.set_face_normal(r, outward_normal);
        get_sphere_uv(outward_normal, rec.u, rec.v);
        rec.mat = mat;

        return true;
    }
    static void get_sphere_uv(const point3 &p, double &u, double &v)
    {
        auto theta = acos(-p.y());
        auto phi = atan2(-p.z(), p.x()) + pi;

        u = phi / (2 * pi);
        v = theta / pi;
    }

    aabb bounding_box() const override { return bbox; }

private:
    point3 center1;
    double radius;
    std::shared_ptr<material> mat;
    bool is_moving;
    vec3 center_vec;
    aabb bbox;
    point3 center(double time) const
    {
        return center1 + time * center_vec;
    }
};

#endif