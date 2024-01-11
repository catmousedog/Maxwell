#pragma once

#include "vec3.hpp"

/**
 * @brief 3 velocity (g, vx*g, vy*g)
 */
struct vel3 : public vec3
{
    using vec3::t;
    using vec3::x;
    using vec3::y;

    vel2 v;

    vel3() : vel3(1, 0, 0) {}
    vel3(const vel2& v) : vel3(v.gamma, v.x * v.gamma, v.y * v.gamma) {}
    vel3(scalar ut, scalar ux, scalar uy) : vec3(ut, ux, uy) { set(); }

    using vec3::mag;
    using vec3::mag2;
    using vec3::normalise;
    using vec3::normalised;

    inline vel3& operator+=(const vec3& v)
    {
        vec3::operator+=(v);
        set();
        return *this;
    }

    inline vec3& operator-=(const vec3& v)
    {
        vec3::operator-=(v);
        set();
        return *this;
    }

    inline vec3& operator*=(scalar a)
    {
        vec3::operator*=(a);
        set();
        return *this;
    }

    inline vec3& operator/=(scalar a)
    {
        vec3::operator/=(a);
        set();
        return *this;
    }

    inline vel3 operator+(const vec3& v) const
    {
        vel3 u = *this;
        return u += v;
    }

    inline vec3 operator-(const vec3& v) const
    {
        vel3 u = *this;
        return u -= v;
    }

    inline vec3 operator*(scalar a) const
    {
        vel3 u = *this;
        return u *= a;
    }

    inline vec3 operator/(scalar a) const
    {
        vel3 u = *this;
        return u /= a;
    }

private:
    void set()
    {
        scalar g = 1 / sqrt(1 + x * x + y * y);
        v = vel2(x * g, y * g);
    }
};
