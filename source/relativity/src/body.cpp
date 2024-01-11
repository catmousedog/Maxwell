#include "../include/body.hpp"
#include <iostream>

void Body::addPoint(const vec2& ppos)
{
    vec2 mpos = vel.contract(ppos);  // mainframe position
    Point* point = new Point(mainframe, vec3(t, x + mpos.x, y + mpos.y));

    scalar A = accel.mag();
    if (A != 0)
    {
        vec2 dir = accel / A;
        scalar d = ppos * dir;       // Rindler distance to point
        scalar a = 1 / (1 / A + d);  // Rindler acceleration
        scalar u = vel.mag * vel.gamma * a / A;
        scalar v = u / sqrt(1 + u * u);
        // point->accel = a * dir;  // not really needed as accel is calculated every step
        point->vel = vel.dir * v;
    }

    points.push_back(point);
    proper_positions.push_back(ppos);
}

// upper case for 'central' point, lower case for other point
void Body::step(scalar dmt)
{
    scalar A = accel.mag();

    if (A == 0)
    {
        for (Point* point : points)
        {
            point->accel = vec2(0, 0);
            point->step(dmt);
        }
    }
    else
    {
        vec2 dir = accel / A;
        scalar D = 1 / A;  // Rindler distance of central point
        for (size_t i = 0; i < points.size(); i++)
        {
            Point* point = points[i];

            const vec2& proper_pos = proper_positions[i];

            scalar d = proper_pos * dir;
            if (d < -D)
            {
                // point is outside the Rindler horizon of the central point
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