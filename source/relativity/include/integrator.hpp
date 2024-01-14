#pragma once

#include "body.hpp"
#include "frame.hpp"
#include <memory>
#include <vector>

class Integrator
{
    Frame& frame;

    std::vector<Body*> bodies;

public:
    Integrator(Frame& frame);

    void addBody(Body* body);

    void setup();

    void step(scalar dmt);

    std::vector<Body*> getBodies();
};