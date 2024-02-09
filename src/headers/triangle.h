#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "myutils.h"
#include "hittable.h"

class triangle : public hittable {
    public:
    triangle(point3 _p1, point3 _p2, point3 _p3, std::shared_ptr<material> _material) : p1(_p1), p2(_p2), p3(_p3), mat(_material) {
        bbox = aabb(aabb(p1, p2), aabb(p2, p3));
    }

    bool hit(const ray& r, interval t, hit_record& rec) const override {
        vec3 normal = unit_vector(cross(p2-p1, p3-p1));
        double d = dot(normal, p1);
        auto n_dot_d = dot(normal, r.direction());
        if(n_dot_d==0){
            return false;
        }

        auto d_m_np = d - dot(normal, r.origin());
        auto t_ = d_m_np / n_dot_d;
        if(!t.surrounds(t_)) return false;
        auto q = r.at(t_);

        auto c1 = dot(cross(p2-p1, q-p1), normal) >= 0;
        auto c2 = dot(cross(p3-p2, q-p2), normal) >= 0;
        auto c3 = dot(cross(p1-p3, q-p3), normal) >= 0;

        if(c1 && c2 && c3){
            rec.t = t_;
            rec.p = r.at(rec.t);
            rec.set_face_normal(r, normal);
            rec.mat = mat;
            return true;
        }else{
            return false;
        }
    }  

    aabb bounding_box() const override { return  bbox;}
    void set_mat(std::shared_ptr<material> _mat) {
        mat = _mat;
    }
    private:
        point3 p1, p2, p3;
        aabb bbox;
        std::shared_ptr<material> mat;
};

class quadrilateral :public hittable{
    public:
        quadrilateral(point3 _p1, point3 _p2, point3 _p3, point3 _p4, std::shared_ptr<material> _material) : t1(_p1, _p2, _p3, _material), t2(_p4, _p1, _p3, _material), mat(_material){
            bbox = aabb(t1.bounding_box(), t2.bounding_box());
        }

        bool hit(const ray& r, interval t, hit_record& rec) const override {
            bool hit_t1 = t1.hit(r, t, rec);
            if(hit_t1){
                bool hit_t2 = t2.hit(r, interval(t.min, rec.t), rec);
                return true;
            }else{
                return t2.hit(r, t, rec);
            }
        }        
    private:
        triangle t1, t2;
        aabb bbox;
        std::shared_ptr<material> mat;
};

#endif