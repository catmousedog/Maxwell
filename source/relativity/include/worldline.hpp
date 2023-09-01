#pragma once

// #include <deque>
#include "vec.hpp"
#include "frame.hpp"

/**
 * Describe the local behaviour of an object. This needs to be able to predict spacetime points
 * (events) of the object's worldline near a given event of the object.
 *
 */

class Worldline
{
protected:
    const Frame &mainframe;

    /**
     * @brief The current event in the mainframe along this worldline.
     */
    vec3 current;

    // const std::deque<vec3> wordline_cache;
    // add some sort of cache list in so integrate can save the cached events along the worldline

    /**
     * @brief Velocity wrt. the mainframe.
     */
    vec2 vel;

public:
    Worldline(const Frame &mainframe);

    /**
     * @brief Get the event at the mainframe time mt.
     *
     * @param t main frame time
     * @return vec3
     */
    vec3 event_at_mtime(const scalar mt) const;

    /**
     * @brief Get the event at the worldline's proper time pt.
     *
     * @param pt worldline's proper time
     * @return vec3
     */
    virtual vec3 event_at_ptime(const scalar pt) const = 0;

    // virtual vec3 integrate(const vec3 event, const scalar dT) const = 0;
};