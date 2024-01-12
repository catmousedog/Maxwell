#include "../include/integrator.hpp"

Integrator::Integrator(const Frame& mainframe) : mainframe(mainframe) {}

void Integrator::addPoint(Point* p)
{
    points.push_back(p);
}

void Integrator::step(const scalar dt)
{
    for (Point* p : points)
    {
        p->step(dt);
    }
}