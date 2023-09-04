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

class Worldline
{
public:
    /**
     * @brief Velocity wrt. the mainframe.
     */
    vel2 vel;

protected:
    const Frame &mainframe;


    // const std::deque<vec3> wordline_cache; add some sort of cache list in so integrate can save
    // the cached events along the worldline

    scalar ptime = 0;

public:
    Worldline(const Frame &mainframe);

    /**
     * @brief Update the current events after a timestep dt in the mainframe.
     *
     * @param t main frame time
     * @return vec3
     */
    void mtime_step(const scalar dmt);

    /**
     * @brief Get the event at the worldline's proper time pt.
     *
     * @param pt proper time
     * @return vec3
     */
    virtual vec3 event_at_ptime(const scalar pt) const = 0;

    /**
     * @brief Velocity at the wordline's proper time pt.
     *
     * @param pt proper time
     * @return vel2
     */
    virtual vel2 vel_at_ptime(const scalar pt) const = 0;
};