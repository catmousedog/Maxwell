#pragma once

#include "../include/worldline.hpp"

#include <math.h>

class PointWorldline : public Worldline
{
public:
    PointWorldline(const Frame &mainframe, const vec2 offset);

    vec3 event_at_ptime(const scalar pt) const override;

    vel2 vel_at_ptime(const scalar pt) const override;

private:
    const vec2 offset;
};