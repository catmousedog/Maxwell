#include "../include/body.hpp"

void Body::addPoint(Point* point)
{
    points.push_back(point);
}

// upper case for 'central' point, lower case for other point
void Body::step(scalar dmt)
{
    accel = vec2(0.1, 0);

    Point::step(dmt);

    vec2 pos = getPos();
    double D = pos.mag();
    pos /= D;

    double A_par = accel * pos;
    vec2 A_per = accel - pos * A_par;

    for (Point* p : points)
    {
        // relative distance to 'central' point of this rigid body
        vec2 rel = pos - p->getPos();
        double d = -rel * pos;

        if (d < -1 / abs(A_par))
        {
            // point is outside the Rindler horizon of the central point
            // seperate this point? create new Body?
        }

        double a_par = D / (D + d) * A_par;  // Rindler factor for constant proper length
        // a_per = A_per

        p->accel = pos * a_par + A_per;

        p->step(dmt);
    }
}