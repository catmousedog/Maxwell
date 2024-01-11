#pragma once

#include "constants.hpp"
#include <math.h>
#include <ostream>

/**
 * @brief space vector for dimension 2
 */
struct vec2
{
    scalar x, y;

    vec2() : x(0), y(0) {}
    vec2(scalar x, scalar y) : x(x), y(y) {}

    inline scalar mag() const { return sqrt(*this * *this); }

    inline scalar mag2() const { return *this * *this; }

    inline vec2& normalise()
    {
        scalar _mag = mag();
        if (_mag != 0) *this /= _mag;
        return *this;
    }

    inline vec2& normalise(scalar& mag)
    {
        mag = vec2::mag();
        if (mag != 0) *this /= mag;
        return *this;
    }

    inline vec2 normalised() const
    {
        vec2 n = *this;
        return n.normalise();
    }

    inline vec2 normalised(scalar& mag)
    {
        vec2 n = *this;
        return n.normalise(mag);
    }

    inline vec2& operator+=(const vec2& u)
    {
        x += u.x;
        y += u.y;
        return *this;
    }

    inline vec2& operator-=(const vec2& u)
    {
        x -= u.x;
        y -= u.y;
        return *this;
    }

    inline vec2& operator*=(const scalar a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    inline vec2& operator/=(const scalar a) { return *this *= (1 / a); }

    inline vec2 operator+(const vec2& u) const
    {
        vec2 v = *this;
        return v += u;
    }

    inline vec2 operator-(const vec2& u) const
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

    inline vec2 operator-() const { return *this * (-1); }

    /**
   * @brief Inner product (+ +)
   *
   * @param u
   * @return scalar
   */
    inline scalar operator*(const vec2& u) const { return x * u.x + y * u.y; }

    inline friend vec2 operator*(const scalar a, const vec2& v) { return v * a; }

    inline friend std::ostream& operator<<(std::ostream& os, const vec2& v) { return os << v.x << "," << v.y; }
};
