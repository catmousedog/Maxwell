#include "../include/worldline.hpp"

#include <math.h>

class PointWorldline : public Worldline
{
public:
    using Worldline::Worldline;

    vec3 event_at_ptime(const scalar pt) const override;

    vel2 vel_at_ptime(const scalar pt) const override;
};