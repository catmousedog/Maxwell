
#include <array>
#include <vector>

typedef float decimal;

typedef std::array<decimal, 2> vec2;

typedef std::array<decimal, 3> vec3;

struct Position
{
    decimal t, x, y;

    Position(decimal t, decimal x, decimal y);
};
