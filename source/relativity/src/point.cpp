#include "../include/point.hpp"

Point::Point(const vec3& pos, const vel2& vel, const vec2& accel) : pos(pos), vel(vel), accel(accel) {}

void Point::step(scalar dmt)
{
    scalar dpt = dmt * vel.igamma;

    pos.t += dmt;
    pos.x += vel.x * dmt;
    pos.y += vel.y * dmt;

    vec2 dv(accel * dpt);
    vel.boost(dv);

    ptime += dpt;
}

std::vector<Point*> Point::getPoints()
{
    return {this};
}