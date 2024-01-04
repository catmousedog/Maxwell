#include "../include/pointworldline.hpp"

#include <math.h>

PointWorldline::PointWorldline(const Frame &mainframe, const vec2 offset) : Worldline(mainframe), offset(offset)
{
    current = vec3(0, offset.x, offset.y);
}

vec3 PointWorldline::event_at_ptime(const scalar pt) const
{
    return vec3(pt, sin(0.5 * pt) + offset.x, offset.y);
}

vel2 PointWorldline::vel_at_ptime(const scalar pt) const
{
    return vel2(0.5 * cos(0.5 * pt) + offset.x, offset.y);
}