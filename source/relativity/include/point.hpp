#pragma once

// #include <deque>
#include "frame.hpp"
#include "vec3.hpp"
#include "vel3.hpp"

/**
 * Describe the local behaviour of an object. This needs to be able to predict spacetime points
 * (events) of the object's worldline near a given event of the object.
 *
 */

class Point
{
protected:
    vel3 U;

    vec3 A;

public:
    vec3 pos;

    vec2 accel;

    scalar ptime = 0;

    Point(const vec3& pos, const vel2& vel = vel2(), const vec2& accel = vec2());

    /**
     * @brief
     *
     * @param dmt main frame timestep
     * @return vec3
     */
    virtual void step(scalar dmt);

    void setVelocity(const vel2& v);

    void setVelocity(scalar Ut, scalar Ux, scalar Uy);

    void boost(const vel2& v);

    void setAccel(const vec2& alpha);
};