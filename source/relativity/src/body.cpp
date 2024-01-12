#include "../include/body.hpp"
#include <iostream>

void Body::addPoint(const vec2& ppos)
{
    vec2 mpos = U.v.contract(ppos);  // mainframe position
    Point* point = new Point(vec3(pos.t, pos.x + mpos.x, pos.y + mpos.y));

    scalar A = accel.mag();
    if (A != 0)
    {
        scalar D = 1 / A;  // Rindler horizon
        vec2 dir = accel * D;
        scalar d = ppos * dir;   // Rindler distance from ref point
        scalar a = 1 / (D + d);  // Rindler acceleration
        scalar u = U.v.mag * U.v.gamma * a / A;
    
        point->setVelocity(1 + u * u, u * U.v.dir.x, u * U.v.dir.y);

        // point->accel = a * dir;  // not really needed as accel is calculated every step
    }

    points.push_back(point);
    ppositions.push_back(ppos);
}

// upper case for 'ref' point, lower case for other point
void Body::step(scalar dmt)
{
    scalar alpha = accel.mag();

    if (alpha == 0)
    {
        for (Point* point : points)
        {
            point->accel = vec2(0, 0);
            point->step(dmt);
        }
    }
    else
    {
        vec2 dir = accel / alpha;
        scalar D = 1 / alpha;  // Rindler distance of ref point
        for (size_t i = 0; i < points.size(); i++)
        {
            Point* point = points[i];

            const vec2& proper_pos = ppositions[i];

            scalar d = proper_pos * dir;
            if (d < -D)
            {
                // point is outside the Rindler horizon of the ref point
                // seperate this point? create new Body?
            }
            else
            {
                scalar a = 1 / (D + d);  // Rindler acceleration A * D/(D+d)

                point->accel = dir * a;
            }

            point->step(dmt);
        }
    }

    Point::step(dmt);
}