#pragma once

#include "vec2.hpp"

struct vel2 : public vec2
{
    scalar mag;
    scalar mag2;
    scalar gamma;
    scalar igamma;

    vec2 dir;

    vel2() : vel2(0, 0) {}
    vel2(scalar vx, scalar vy) : vec2(vx, vy)
    {
        mag2 = vec2::mag2();
        mag = sqrt(mag2);
        igamma = sqrt(1 - mag2);
        gamma = 1 / igamma;
        dir = *this;
        if (mag != 0) dir /= mag;
    }
    vel2(const vel2& v) : vec2(v.x, v.y)
    {
        mag = v.mag;
        mag2 = v.mag2;
        gamma = v.gamma;
        igamma = v.igamma;
        dir = v.dir;
    }
    vel2(const vec2& v) : vel2(v.x, v.y) {}

    inline vec2 contract(const vec2& pos) const
    {
        scalar l_par = pos * dir;
        vec2 l_per = pos - l_par * dir;

        return l_par * dir * igamma + l_per;
    }

    /**
     * @brief Non-commutative relativistic velocity addition. The first velocity is the original
     * velocity in the 'rest' frame, the second velocity is the velocity of the boost.
     *
     * @param v the boost velocity
     * @return vel2&
     */
    inline vel2& boost(const vel2& v)
    {
        scalar u_par = v.dir * *this;
        vec2 u_per = *this - u_par * v.dir;

        scalar g = 1 / (1 + u_par * v.mag);
        scalar bu_par = (v.mag + u_par) * g;
        vec2 bu_per = u_per * v.igamma * g;

        *this = vel2(bu_par * v.dir + bu_per);
        return *this;
    }

    inline vel2 boosted(const vel2& v) const
    {
        vel2 u = *this;
        return u.boost(v);
    }
};
