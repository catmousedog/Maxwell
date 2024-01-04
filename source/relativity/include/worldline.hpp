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
     * @brief Velocity of the initial starting frame wrt. the mainframe. This does not include the
     * derivative of the worldline dx/dtau.
     */
    vel2 vel;

    /**
     * @brief The worldline velocity wrt. to the initial starting frame of the worldline. This is
     * equal to the derivative dx/dtau of this worldline.
     */
    vel2 wvel;

    vec3 current;

    scalar ptime = 0;

protected:
    const Frame &mainframe;


    // const std::deque<vec3> wordline_cache; add some sort of cache list in so integrate can save
    // the cached events along the worldline

public:
    Worldline(const Frame &mainframe);

    /**
     * @brief 
     *
     * @param dmt main frame timestep
     * @return vec3
     */
    void dt_step(const scalar dmt);

    /**
     * @brief 
     *
     * @param dv vel step
     * @return vec3
     */
    void dv_step(const vel2 dv);

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