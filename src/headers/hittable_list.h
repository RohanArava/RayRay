#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
    public:
        std::vector<std::shared_ptr<hittable>> objects;
        
        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> object) { add(object); }

        void clear() {objects.clear();}

        void add(std::shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval t, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = t.max;
    
            for (const auto& object : objects) {
                if (object->hit(r, interval(t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
    
            return hit_anything;
        }
};

#endif