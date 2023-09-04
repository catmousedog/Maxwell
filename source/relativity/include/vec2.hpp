#pragma once

#include "constants.hpp"

#include <math.h>

/**
 * @brief space vector for dimension 2
 */
struct vec2
{
    scalar x, y;

    vec2() : x(0), y(0) {}
    vec2(scalar x, scalar y) : x(x), y(y) {}

    inline scalar mag() const
    {
        return sqrt(*this * *this);
    }

    inline vec2 &normalise()
    {
        scalar _mag = mag();
        if (_mag != 0)
            *this /= _mag;
        return *this;
    }

    inline vec2 &operator+=(const vec2 &u)
    {
        x += u.x;
        y += u.y;
        return *this;
    }

    inline vec2 &operator-=(const vec2 &u)
    {
        x -= u.x;
        y -= u.y;
        return *this;
    }

    inline vec2 &operator*=(const scalar a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    inline vec2 &operator/=(const scalar a)
    {
        return *this *= (1 / a);
    }

    inline vec2 operator+(const vec2 &u) const
    {
        vec2 v = *this;
        return v += u;
    }

    inline vec2 operator-(const vec2 &u) const
    {
        vec2 v = *this;
        return v -= u;
    }

    inline vec2 operator*(const scalar a) const
    {
        vec2 u = *this;
        return u *= a;
    }

    inline vec2 operator/(const scalar a) const
    {
        vec2 u = *this;
        return u /= a;
    }

    /**
     * @brief Inner product (+ +)
     *
     * @param u
     * @return scalar
     */
    inline scalar operator*(const vec2 &u) const
    {
        return x * u.x + y * u.y;
    }
};
