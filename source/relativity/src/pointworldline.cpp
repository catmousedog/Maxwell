#include "../include/pointworldline.hpp"

#include <math.h>

vec3 PointWorldline::event_at_ptime(const scalar pt) const
{
    return vec3(pt, sin(0.5 * pt), 0);
}

vel2 PointWorldline::vel_at_ptime(const scalar pt) const
{
    return vel2(0, 0.5 * cos(0.5 * pt));
}