
#include "../include/vec3.h"

#include <cmath>

vec2::vec2(scalar x, scalar y) : x(x), y(y) {}

vec2 vec2::operator+(const vec2 &other) const
{
    return vec2(x + other.x, y + other.y);
}

scalar vec2::operator*(const vec2 &other) const
{
    return x * other.x + y * other.y;
}

vec2 operator*(const vec2 &a, const scalar b)
{
    return vec2(a.x * b, a.y * b);
}

vec2 operator*(const scalar a, const vec2 &b)
{
    return b * a;
}

vec3::vec3(scalar t, scalar x, scalar y) : t(t), x(x), y(y) {}

// should probably optimise this to that multiple spacetime events can be boosted at once
vec3 vec3::boost(const vec2 &v) const
{
    const vec2 n = v.normalise();
    const scalar v_norm2 = v * v;
    const scalar v_norm = std::sqrt(v_norm2);
    const scalar g = 1 / std::sqrt(1 - v_norm2);

    vec2 r = vec2(x, y);
    const scalar r_n = n * r;

    scalar t_1 = g * (t - v_norm * r_n / c2);
    vec2 r_1 = r + n * (g * (r_n + v_norm * t) - r_n);
    return vec3(t_1, r_1.x, r_1.y);
}

scalar vec3::operator*(const vec3 &other) const
{
    // minkowski metric for now
    return t * other.t - x * other.x - y * other.y;
}
