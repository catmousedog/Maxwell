
#include <array>
#include <vector>

typedef float decimal;

typedef std::array<decimal, 2> vec2;

typedef std::array<decimal, 3> vec3;

typedef std::vector<vec2> Polygon;

struct Event
{
    decimal x, y, t;

    Event(decimal x, decimal y, decimal t);
};

struct SpatialEvent
{
    decimal x, y;

    SpatialEvent(decimal x, decimal y);
};
