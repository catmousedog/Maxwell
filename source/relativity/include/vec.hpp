#pragma once

#include <math.h>

typedef double scalar;

#define GAMMA(V) 1.0 / sqrt(1.0 - V * V)

/**
 * @brief space vector for dimension 2
 */
struct vec2
{
    scalar x, y;

    /**
     * @brief Inner product (+ +)
     *
     * @param v
     * @return scalar
     */
    inline scalar operator*(const vec2 &v) const
    {
        return x * v.x + y * v.y;
    }

    inline scalar mag() const
    {
        return sqrt(*this * *this);
    }

    inline vec2 &operator*=(const scalar a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    inline vec2 &operator/=(const scalar a)
    {
        x /= a;
        y /= a;
        return *this;
    }
};

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

    void boost(const vec2 &vel)
    {
        scalar v = vel.mag();
        scalar g = GAMMA(v);
        vec2 dir = vel;
        dir /= v;

        scalar old_t = t;

        // just vx for now
        t = g * (old_t - v * x);
        x = g * (x - v * old_t);
    }

    // 1st ground form (metric)
    /**
     * @brief Minkowski inner product (+ - -)
     *
     * @param V
     * @return scalar
     */
    scalar operator*(const vec3 &v) const
    {
        return t * v.t - x * v.x - y * v.y;
    }

    // 2nd ground form
};
