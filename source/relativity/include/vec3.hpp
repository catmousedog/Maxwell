#pragma once

#include "constants.hpp"
#include "vec2.hpp"
#include "vel2.hpp"
#include <ostream>
#include <iostream>

/**
 * @brief spacetime vector of dimension 3
 */
struct vec3
{
    /**
     * @brief Cartesian spacetime coordinates
     */
    scalar t, x, y;

    // perhaps some enum for cartesian, cylindrical, ...?

    vec3() : t(0), x(0), y(0) {}
    vec3(scalar t, scalar x, scalar y) : t(t), x(x), y(y) {}

    inline vec2 pos() const { return vec2(x, y); }

    inline vec3& boost(const vel2& u)
    {
        scalar old_t = t;

        // parallel
        scalar r_par = u.dir.x * x + u.dir.y * y;

        // perp
        vec2 r_per(x - u.dir.x * r_par, y - u.dir.y * r_par);

        t = u.gamma * (old_t + u.mag * r_par);
        scalar br_par = u.gamma * (r_par + u.mag * old_t);

        vec2 boosted = u.dir * br_par + r_per;
        x = boosted.x;
        y = boosted.y;

        return *this;
    }

    inline vec3 boosted(const vel2& u)
    {
        vec3 v = *this;
        return v.boost(u);
    }

    inline vec3& operator+=(const vec3& u)
    {
        t += u.t;
        x += u.x;
        y += u.y;
        return *this;
    }

    inline vec3& operator-=(const vec3& u)
    {
        t -= u.t;
        x -= u.x;
        y -= u.y;
        return *this;
    }

    inline vec3 operator+(const vec3& u) const
    {
        vec3 v = *this;
        return v += u;
    }

    inline vec3 operator-(const vec3& u) const
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
    inline scalar operator*(const vec3& u) const { return t * u.t - x * u.x - y * u.y; }

    // 2nd ground form

    inline bool operator==(const vec3& u) const { return t == u.t && x == u.x && y == u.y; }

    inline friend std::ostream& operator<<(std::ostream& os, const vec3& v)
    {
        return os << v.t << "," << v.x << "," << v.y;
    }
};
