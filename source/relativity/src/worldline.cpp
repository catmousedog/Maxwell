#include "../include/worldline.hpp"

Worldline::Worldline(const Frame &mainframe) : mainframe(mainframe)
{
}

void Worldline::mtime_step(const scalar dmt)
{
    // in reality this will have to be a converging process because this is only true for a straight
    // world line, so an iterative process is needed to find the right dpt such that it is at t+dmt
    scalar dpt = vel.igamma() * dmt;

    // previous
    vec3 prev_e = event_at_ptime(ptime);
    vel2 prev_v = vel_at_ptime(ptime);

    // next
    ptime += dpt;

    vel2 dv = vel_at_ptime(ptime) - prev_v;
    vec3 ds = event_at_ptime(ptime) - prev_e;

    ds.boost(vel);
    vel.boost(dv);
}