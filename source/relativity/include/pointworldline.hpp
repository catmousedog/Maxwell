#include "../include/worldline.hpp"

#include <math.h>

class PointWorldline : public Worldline
{
public:
    using Worldline::Worldline;

    vec3 event_at_ptime() const override;
};