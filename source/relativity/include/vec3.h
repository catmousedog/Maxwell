#pragma once

#include <array>
#include <vector>

typedef float scalar;

constexpr scalar c = 1;
constexpr scalar c2 = c * c;

struct vec2
{
    scalar x, y;

    vec2(scalar x, scalar y);

    vec2 normalise() const;

    scalar operator*(const vec2 &other) const;
    vec2 operator+(const vec2& other) const;

    friend vec2 operator*(const vec2 &a, const scalar b);
    friend vec2 operator*(const scalar a, const vec2 &b);
};

struct vec3
{
    scalar t, x, y;

    vec3(scalar t, scalar x, scalar y);

    vec3 boost(const vec2 &v) const;

    // minkowski inner product
    scalar operator*(const vec3 &other) const;
};
