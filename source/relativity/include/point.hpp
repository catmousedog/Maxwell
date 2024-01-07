#pragma once

// #include <deque>
#include "frame.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vel2.hpp"

/**
 * Describe the local behaviour of an object. This needs to be able to predict spacetime points
 * (events) of the object's worldline near a given event of the object.
 *
 */

class Point
{
public:
    /**
     * @brief Velocity in the mainframe.
     */
    vel2 vel;

    /**
     * @brief Current position and time in the mainframe.
     */
    vec3 current;

    /**
     * @brief Proper acceleration.
     */
    vec2 accel;

    /**
     * @brief Proper time.
     */
    scalar ptime = 0;

protected:
    const Frame& mainframe;

    // add some sort of cache list in so integrate can save the cached events along the worldline
    // const std::deque<vec3> wordline_cache;

public:
    Point(const Frame& mainframe);

    Point(const Frame& mainframe, const vec3& current);

    /**
     * @brief
     *
     * @param dmt main frame timestep
     * @return vec3
     */
    virtual void step(scalar dmt);

    vec2 getPos() const;
};