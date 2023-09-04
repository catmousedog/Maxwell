#pragma once

#include "constants.hpp"
#include "vec2.hpp"
#include "vel2.hpp"

/**
 * @brief spacetime vector of dimension 3
 */
struct vec3
{
    /**
     * @brief arbitrary spacetime coordinates
     */
    scalar t, x, y;

    // perhaps some enum for cartesian, cylindrical, ...?

    vec3() : t(0), x(0), y(0) {}
    vec3(scalar t, scalar x, scalar y) : t(t), x(x), y(y) {}

    void boost(const vel2 &v)
    {
        scalar old_t = t;

        // just vx for now
        t = v.gamma() * (old_t - v.mag() * x);
        x = v.gamma() * (x - v.mag() * old_t);
    }

    vec3 &operator+=(const vec3 &u)
    {
        t += u.t;
        x += u.x;
        y += u.y;
        return *this;
    }

    vec3 &operator-=(const vec3 &u)
    {
        t -= u.t;
        x -= u.x;
        y -= u.y;
        return *this;
    }

    vec3 operator+(const vec3 &u) const
    {
        vec3 v = *this;
        return v += u;
    }

    vec3 operator-(const vec3 &u) const
    {
        vec3 v = *this;
        return v -= u;
    }

    // 1st ground form (metric)
    /**
     * @brief Minkowski inner product (+ - -)
     *
     * @param u
     * @return scalar
     */
    scalar operator*(const vec3 &u) const
    {
        return t * u.t - x * u.x - y * u.y;
    }

    // 2nd ground form
};
