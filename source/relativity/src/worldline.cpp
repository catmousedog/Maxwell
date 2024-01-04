#include "../include/worldline.hpp"

Worldline::Worldline(const Frame &mainframe) : mainframe(mainframe)
{
}

void Worldline::dt_step(const scalar dt)
{
    // in reality this will have to be a converging process because this is only true for a straight
    // world line, so an iterative process is needed to find the right dpt such that it is at t+dmt

    scalar dpt = dt;

    // previous
    vec3 prev_e = event_at_ptime(ptime);
    // vel2 prev_v = vel_at_ptime(ptime);

    // next
    ptime += dpt;

    // vel2 dv = vel_at_ptime(ptime) - prev_v;
    vec3 ds = event_at_ptime(ptime) - prev_e;

    current += ds.boost(vel);
    // vel.boost(dv);
}

void Worldline::dv_step(const vel2 dv)
{
    // scalar dt = sqrt(1-vel*vel)*dv*x_{0}/(1-vel*wvel-wvel*dv+vel*dv);
    // scalar dx = \frac{1}{\sqrt{1-dv^{2}}}*\frac{x_{0}(wvel* vel(1-dv^{2})-(1-dv^{2}))}{(dv*(wvel-vel)+wvelvel-1)}
    
    vel.boost(dv);
}