#include "../include/point.hpp"

Point::Point(const vec3& pos, const vel2& vel, const vec2& accel) : pos(pos), U(vel), accel(accel) {}

void Point::step(scalar dmt)
{
    scalar dpt = dmt * U.v.igamma;

    pos.t += dmt;
    pos.x += U.v.x * dmt;
    pos.y += U.v.y * dmt;
    // pos += U * dpt;       // more compact but unnecessary gamma * and /
    A = accel.boosted(U.v);  // boost the proper accel to the comoving frame
    U += A * dpt;            // A = dU/dtau

    ptime += dpt;
}

void Point::setVelocity(const vel2& v)
{
    U = v;
}

void Point::setVelocity(scalar Ut, scalar Ux, scalar Uy)
{
    this->U = vel3(Ut, Ux, Uy);
}

void Point::setAccel(const vec2& alpha)
{
    accel = alpha;
}