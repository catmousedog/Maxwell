#pragma once

#include "point.hpp"
#include <vector>

/**
 * @brief A rigid body. Although technically not possible since it would break
 * causality, the worldlines of this body move in such a way it remains the same
 * proper lengths.
 */
class Body : public Point
{
public:
    std::vector<Point*> points;

    using Point::Point;

    void addPoint(Point* point);

    void step(scalar dmt) override;
};