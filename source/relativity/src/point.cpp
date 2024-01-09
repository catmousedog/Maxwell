#include "../include/point.hpp"
#include <iostream>

Point::Point(const Frame& mainframe) : mainframe(mainframe) {}

Point::Point(const Frame& mainframe, const vec3& event) : vec3(event), mainframe(mainframe) {}

void Point::step(scalar dmt)
{
    // might have to do multiple Point steps if dpt becomes too high!
    scalar dpt = dmt * vel.igamma;

    // previous
    // vel2 prev_v = vel_at_ptime(ptime);
    // vec3 prev_e = event_at_ptime(ptime);

    // next
    ptime += dpt;

    // vel2 dv = vel_at_ptime(ptime) - prev_v;
    // vec3 ds = event_at_ptime(ptime) - prev_e;

    // simple 1st order timestep
    vec2 dl = vel * dmt;
    *this += vec3(dmt, dl.x, dl.y);

    // change velocity of this object somehow
    vel2 dv(accel * dpt);
    vel.boost(dv);
}
