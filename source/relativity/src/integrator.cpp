#include "../include/integrator.hpp"
#include "../include/vel2.hpp"

Integrator::Integrator(Frame& frame) : frame(frame) {}

void Integrator::addBody(Body* body)
{
    bodies.push_back(body);
}

void Integrator::setup()
{
    for (Body* body : bodies) body->setup();
}

void Integrator::step(scalar dt)
{
    vel2 dv = vel2(frame.accel * (-dt));  // make dv opposite to perform Lorentz boost
    for (Body* body : bodies)
    {
        body->step(dt);
        // p->boost(dv);
    }
    frame.time += dt;
}

std::vector<Body*> Integrator::getBodies()
{
    return bodies;
}