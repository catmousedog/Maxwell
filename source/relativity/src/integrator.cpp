#include "../include/integrator.hpp"

Integrator::Integrator(const Frame &mainframe) : mainframe(mainframe)
{
}

void Integrator::add_worldline(const vec2 offset)
{
    PointWorldline *pwl = new PointWorldline(mainframe, offset);
    objects.push_back(std::unique_ptr<Worldline>(pwl));
}

void Integrator::step(const scalar dt)
{
    vel2 dv(0.01, 0);
    for (std::unique_ptr<Worldline> &ptr : objects)
    {
        Worldline &wl = *ptr.get();
        wl.dt_step(dt);
        wl.vel.boost(-dv);
    }
}