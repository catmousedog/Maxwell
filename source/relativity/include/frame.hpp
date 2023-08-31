#pragma once

/**
 * @brief A (momentarily) inertial frame to use coordinates in.
 */
struct Frame
{
    // vec3 events[] // all events at t=0

    // somehow step the main frame forward and linearize the changes in events such that we don't have to ray march / implicit solve every frame

    /**
     * IDEA: we first do an implicit calculation of all events to get vec3 events
     *
     * then we move our frame through spacetime and adjust events linearly (so just move points up)
     *
     * then we change our velocity and adjust events again (is this just a lorentz boost of the
     * prev. point?)
     *
     * changing events: this means we do small steps along the worldline of the object of the event,
     * we cache any points we calculate so that in the future we can reuse them if we see the same
     * spacetime point again if these events of a certain object fall below the past lightcone we
     * can safely delete them
     *
     * this means we only need the LOCAL behaviour of our objects!!! great! we just need to
     * calculate the implicit events of all objects once in the beginning
     *
     * Maybe still implement a ray marcher on GPU later?
     *
     * SUMMARY: the gameloop will be as follow:
     *
     * initialise by implicitly solving for all events (these are vec3 points each belonging to some
     * object)
     *
     * then move observer frame according to its velocity -> this is actually just moving forward in
     * time!! since we are using the observer frame as the "global" frame (non inertial only
     * momentarily interial!!)
     *
     * now you have new events save these and boost the observer frame according to how well the
     * observer moves
     *
     * find the new event that intersects the now t=0 plane after the Lorentz boost, this will be
     * the new event
     *
     * now do inverse Lorentz boost for each object event to find the coordinates in our now new
     * rest frame
     *
     */
};