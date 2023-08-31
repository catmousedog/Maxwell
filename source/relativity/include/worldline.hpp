#pragma once

#include "vec.hpp"
#include "frame.hpp"

/**
 * Describe the local behaviour of an object. This needs to be able to predict spacetime points
 * (events) of the object's worldline near a given event of the object.
 *
 */

struct Worldline
{

    const Frame &mainframe;

    Worldline(const Frame &mainframe);

    // virtual 

    // might need more params? or is all info contained in mainframe?
    virtual vec3 neighbouring(const vec3 &event) const;
};