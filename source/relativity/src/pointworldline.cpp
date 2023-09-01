#include "../include/pointworldline.hpp"

#include <math.h>

vec3 PointWorldline::event_at_ptime(const scalar pt) const
{
    return vec3(pt, sin(0.5 * pt), 0);
}