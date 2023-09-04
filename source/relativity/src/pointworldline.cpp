#include "../include/pointworldline.hpp"

#include <math.h>

vec3 PointWorldline::event_at_ptime() const
{
    return vec3(ptime, sin(0.5 * ptime), 0);
}