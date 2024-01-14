#pragma once

#include "constants.hpp"
#include <vector>

struct Point;

class Body
{
public:
    virtual ~Body() = default;

    virtual void setup() {}

    virtual void step(scalar dmt) = 0;

    virtual std::vector<Point*> getPoints() = 0;
};
