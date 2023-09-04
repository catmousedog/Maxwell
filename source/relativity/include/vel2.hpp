#pragma once

#include "vec2.hpp"
#include "ostream"

struct vel2 : public vec2
{
private:
    using vec2::x;
    using vec2::y;

    scalar _mag;
    scalar _gamma;
    scalar _igamma;

    vec2 _dir;

public:
    vel2() : vec2()
    {
        set(x, y);
    }
    vel2(scalar vx, scalar vy) : vec2(vx, vy)
    {
        set(x, y);
    }
    vel2(const vec2 &vec) : vec2(vec.x, vec.y)
    {
        set(x, y);
    }

    inline scalar vx() const { return x; }
    inline scalar vy() const { return y; }
    inline scalar mag() const { return _mag; }
    inline scalar gamma() const { return _gamma; }
    inline scalar igamma() const { return _igamma; }
    inline vec2 dir() const { return _dir; }

    inline vel2 &operator=(const vel2 &vel)
    {
        x = vel.x;
        y = vel.y;
        _mag = vel._mag;
        _igamma = vel._igamma;
        _gamma = vel._gamma;
        _dir = vel._dir;
        return *this;
    }

    inline vel2 &operator=(const vec2 &vec)
    {
        set(vec.x, vec.y);
        return *this;
    }

    /**
     * @brief Non-commutative relativistic velocity addition. The first velocity is the original
     * velocity in the 'rest' frame, the second velocity is the velocity of the boost.
     *
     * @param u the boost velocity
     * @return vel2&
     */
    inline vel2 &boost(const vel2 &u)
    {
        vel2 &v = *this;
        // parallel
        scalar v_par = u._dir * v;
        scalar g = 1 / (1 + u._mag * v_par);
        scalar bv_par = (v_par + u._mag) * g;

        // perp
        vec2 v_per = static_cast<vec2 &>(v) - u._dir * v_par; // not a vel since we just need mag()
        vec2 bv_per = v_per * u._igamma * g;

        *this = u._dir * bv_par + bv_per;

        return *this;
    }

    /**
     * @brief Relativistic velocity addition. The first velocity is the original velocity in the
     * 'rest' frame, the second velocity is the velocity of the boost.
     *
     * @param u the boost velocity
     * @return vel2
     */
    inline vel2 boosted(const vel2 &u)
    {
        vel2 v = *this;
        return v.boost(u);
    }

private:
    inline void set(scalar vx, scalar vy)
    {
        x = vx;
        y = vy;
        _mag = vec2::mag();
        _igamma = sqrt(1 - _mag * _mag);
        _gamma = 1 / _igamma;
        _dir = *this;
        _dir.normalise();
    }

    friend std::ostream &operator<<(std::ostream &os, const vel2 &vel)
    {
        os << vel.x << ", " << vel.y;
        return os;
    }

    friend class vec3;
};
