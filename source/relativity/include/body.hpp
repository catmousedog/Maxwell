#pragma once

#include "point.hpp"
#include <iostream>
#include <vector>

/**
 * @brief A rigid body. Although technically not possible since it would break
 * causality, the worldlines of this body move in such a way it remains the same
 * proper lengths.
 */
class Body : public Point
{

    std::vector<Point*> points;

    /**
     * @brief Proper positions associated with each point.
     */
    std::vector<vec2> ppositions;

public:
    using Point::Point;

    void addPoint(const vec2& ppos);

    void step(scalar dmt) override;

    std::vector<Point*> getPoints() { return points; }
};