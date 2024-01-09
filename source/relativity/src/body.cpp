#include "../include/body.hpp"
#include <iostream>

void Body::addPoint(const vec2& ppos)
{
    // lorentz transform is needed here as body might be moving wrt to mainframe
    points.push_back(new Point(mainframe, vec3(t, x + ppos.x, y + ppos.y)));
    proper_positions.push_back(ppos);
}

// upper case for 'central' point, lower case for other point
void Body::step(scalar dmt)
{
    vec2 dir = pos().normalise();

    double A_par = accel * dir;
    vec2 A_per = accel - dir * A_par;
    double V_par = vel * dir;

    // Rindler distance of central point
    double D = 1 / A_par;
    // D = 1 / A_par * (1 - vel.gamma) + D;

    for (size_t i = 0; i < points.size(); i++)
    {
        Point* point = points[i];
        const vec2& proper_pos = proper_positions[i];

        double d = -proper_pos * dir;
        if (d > D)
        {
            // point is outside the Rindler horizon of the central point
            // seperate this point? create new Body?
        }
        else
        {
            double a_par = D / (D + d) * A_par;  // Rindler factor for constant proper length

            point->accel = dir * a_par + A_per;  // a_per = A_per

            point->step(dmt);
        }
    }

    Point::step(dmt);
}