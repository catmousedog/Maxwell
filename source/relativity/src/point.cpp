#include "../include/point.hpp"

Point::Point(const vec3& pos, const vel2& vel, const vec2& accel) : pos(pos), U(vel), accel(accel) {}

void Point::step(scalar dmt)
{
    scalar dpt = dmt * U.v.igamma;

    pos += U * dpt; // make this more accurate by splitting the addition U0 = gamma
    A = accel.boosted(U.v);
    U += A * dpt;
    // U.normalise();

    ptime += dpt;
}
