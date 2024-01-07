#include "../include/point.hpp"

Point::Point(const Frame& mainframe) : mainframe(mainframe) {}

Point::Point(const Frame& mainframe, const vec3& current) : mainframe(mainframe), current(current) {}

void Point::step(scalar dmt)
{
    // in reality this will have to be a converging process because this is only true for a straight
    // world line, so an iterative process is needed to find the right dpt such that it is at t+dmt

    scalar dpt = dmt * vel.igamma();

    // previous
    // vel2 prev_v = vel_at_ptime(ptime);
    // vec3 prev_e = event_at_ptime(ptime);

    // next
    ptime += dpt;

    // vel2 dv = vel_at_ptime(ptime) - prev_v;
    // vec3 ds = event_at_ptime(ptime) - prev_e;

    // simple 1st order timestep
    vec2 dl = vel * dmt;
    current += vec3(dmt, dl.x, dl.y);

    // change velocity of this object somehow
    vel2 dv(accel * dpt);
    vel.boost(dv);
}

vec2 Point::getPos() const
{
    return vec2(current.x, current.y);
}