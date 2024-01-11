#include "../include/point.hpp"
#include <iostream>

Point::Point(const Frame& mainframe) : mainframe(mainframe) {}

Point::Point(const Frame& mainframe, const vec3& event) : vec3(event), mainframe(mainframe) {}

void Point::step(scalar dmt)
{
    // might have to do multiple Point steps if dpt becomes too high!
    scalar dpt = dmt * vel.igamma;

    // simple 1st order pos timestep
    vec2 dl = vel * dmt;
    *this += vec3(dmt, dl.x, dl.y);

    // simple 1st order vel timestep
    double g = vel.gamma;
    vec2 dv(accel * dpt);
    // vec2 dv(accel * dpt / (g + vel.mag2 * g * g * g));

    vel.boost(dv);

    ptime += dpt;
}
