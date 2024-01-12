#include "../include/integrator.hpp"

Integrator::Integrator(const Frame& frame) : frame(frame) {}

void Integrator::addPoint(Point* p)
{
    points.push_back(p);
}

void Integrator::step(const scalar dt)
{
    vel2 dv = vel2(frame.accel * (-dt));  // make dv opposite to perform Lorentz boost
    for (Point* p : points)
    {
        p->step(dt);
        p->boost(dv);
    }
}