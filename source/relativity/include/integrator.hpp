#pragma once

#include "point.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vel2.hpp"
#include <memory>
#include <vector>

class Integrator
{
    const Frame& frame;

    std::vector<Point*> points;

public:
    Integrator(const Frame& frame);

    void addPoint(Point* p);

    void step(const scalar dt);

    std::vector<Point*> getPoints() { return points; }
};