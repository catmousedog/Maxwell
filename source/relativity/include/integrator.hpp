#pragma once

#include <vector>
#include <memory>

#include "worldline.hpp"
#include "pointworldline.hpp"
#include "vec2.hpp"
#include "vel2.hpp"
#include "vec3.hpp"

class Integrator
{
    const Frame &mainframe;

    std::vector<std::unique_ptr<Worldline>> objects;

public:
    Integrator(const Frame &mainframe);

    void add_worldline(const vec2 offset);

    void step(const scalar dt);
};