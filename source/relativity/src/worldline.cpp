#include "../include/worldline.hpp"

Worldline::Worldline(const Frame &mainframe) : mainframe(mainframe)
{
}

void Worldline::update_current_mtime_step(const scalar dmt)
{
    scalar dpt = vel.igamma() * dmt;
    ptime += dpt;

    vec3 next_event = event_at_ptime();
    vec3 delta = next_event - pcurrent;


    // we have vel wrt. mainframe so we just have to calculate change in velocity of the worldline and relativisticly add it to the current v.

    // do lorentz boost and get event in frame m
}