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
     * @brief Cartesian spacetime coordinates
     */
    scalar t, x, y;

    // perhaps some enum for cartesian, cylindrical, ...?

    vec3() : t(0), x(0), y(0) {}
    vec3(scalar t, scalar x, scalar y) : t(t), x(x), y(y) {}
    vec3(const vec3& v) = default;

    inline vec2 getPos() const { return vec2(x, y); }

    inline scalar mag() const { return sqrt(*this * *this); }

    inline scalar mag2() const { return *this * *this; }

    /**
     * @brief Normalises a timelike vec3. 
     * This won't work on spacelike as it will always return a vec3 with positive magnitude.
     * @return vec3& 
     */
    inline vec3& normalise()
    {
        scalar _mag = mag();
        if (_mag != 0) *this /= _mag;
        return *this;
    }

    inline vec3& normalise(scalar& mag)
    {
        mag = vec3::mag();
        if (mag != 0) *this /= mag;
        return *this;
    }

    inline vec3 normalised() const
    {
        vec3 n = *this;
        return n.normalise();
    }

    inline vec3 normalised(scalar& mag) const
    {
        vec3 n = *this;
        return n.normalise(mag);
    }

    inline vec3& boost(const vel2& v)
    {
        scalar old_t = t;

        scalar r_par = v.dir.x * x + v.dir.y * y;
        vec2 r_per(x - v.dir.x * r_par, y - v.dir.y * r_par);

        t = v.gamma * (old_t + v.mag * r_par);
        scalar br_par = v.gamma * (r_par + v.mag * old_t);

        vec2 boosted = v.dir * br_par + r_per;
        x = boosted.x;
        y = boosted.y;

        return *this;
    }

    inline vec3 boosted(const vel2& v)
    {
        vec3 u = *this;
        return u.boost(v);
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

    inline vec3& operator*=(scalar a)
    {
        t *= a;
        x *= a;
        y *= a;
        return *this;
    }

    inline vec3& operator/=(scalar a)
    {
        scalar ia = 1 / a;
        t *= ia;
        x *= ia;
        y *= ia;
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

    inline vec3 operator*(scalar a) const
    {
        vec3 v = *this;
        return v *= a;
    }

    inline vec3 operator/(scalar a) const
    {
        vec3 v = *this;
        return v /= a;
    }

    // 1st ground form (metric)
    /**
     * @brief Minkowski inner product (+ - -)
     *
     * @param u
     * @return scalar
     */
    inline scalar operator*(const vec3& u) const { return t * u.t - x * u.x - y * u.y; }
};

vec3 vec2::boosted(const vel2& v) const
{
    scalar r_par = v.dir.x * x + v.dir.y * y;
    vec2 r_per(x - v.dir.x * r_par, y - v.dir.y * r_par);

    scalar t = v.gamma * v.mag * r_par;
    scalar br_par = v.gamma * r_par;

    vec2 boosted = v.dir * br_par + r_per;

    return vec3(t, boosted.x, boosted.y);
}