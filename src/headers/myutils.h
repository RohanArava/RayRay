#ifndef MYUTILS_H
#define MYUTILS_H

#include <cmath>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

void print_ppm(std::ostream &out);

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif
