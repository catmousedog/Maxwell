#pragma once

#include "frame.hpp"
#include "point.hpp"
#include <queue>
#include <vector>

/**
 * @brief A rigid body. Although technically not possible since it would break
 * causality, the worldlines of this body move in such a way it remains the same
 * proper lengths.
 */
class RigidBody : public Body
{
private:
    struct RigidPoint : public Point
    {
        const vec2 ppos;
        std::queue<std::pair<scalar, vec2>> scheduled_accels;

        RigidPoint(const vec2& mpos, const vec2& ppos);
    };

    /**
     * @brief Frame time when the reference point (ppos = 0,0) can accelerate again.
     * This is used to determina whether the RigidBody can accelerate using updateAccel
     */
    scalar ref_time;

    /**
     * @brief The coordinates around which the points will be placed.
     * This is not a Point itself, it is just used to place the Points.
     */
    const vec2 ref_mpos;
    const vel2 vel_init;
    vec2 ref_accel;

    std::vector<RigidPoint*> rigid_points;

    const Frame& frame;

    bool setup_done = false;

public:
    RigidBody(const Frame& frame, const vec2& ref_mpos, const vel2& vel_init, const vec2& ref_accel);

    ~RigidBody();

    Point* addPoint(const vec2& ppos);

    bool updateAccel(const vec2& accel);

    std::vector<Point*> getPoints() override;

private:
    void setup() override;

    void step(scalar dmt) override;
};