#pragma once

#include "body.hpp"
#include "vec3.hpp"

class RigidBody;

/**
 * Describe the local behaviour of an object. This needs to be able to predict spacetime points
 * (events) of the object's worldline near a given event of the object.
 *
 */

class Point : public Body
{
public:
    vec3 pos;

    vel2 vel;

    vec2 accel;

    scalar ptime = 0;

    Point(const vec3& pos, const vel2& vel = vel2(), const vec2& accel = vec2());

    /**
     * @brief
     *
     * @param dmt main frame timestep
     * @return vec3
     */
    virtual void step(scalar dmt) override;

    std::vector<Point*> getPoints() override;

    friend RigidBody;
};