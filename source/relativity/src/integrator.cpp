#include "../include/integrator.hpp"

Integrator::Integrator(const Frame& mainframe) : mainframe(mainframe) {}

void Integrator::addPoint(Point* p)
{
    points.push_back(p);
}

void Integrator::step(const scalar dt)
{
    vel2 dv(0.01, 0);
    for (Point* p : points)
    {
        p->step(dt);
        // wl->vel.boost(-dv);
    }
}