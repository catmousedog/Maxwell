#include "../include/worldline.hpp"

Worldline::Worldline(const Frame &mainframe) : mainframe(mainframe)
{
}

vec3 Worldline::event_at_mtime(const scalar mt) const
{
    // figure out how to sync mt and pt in the beginning?
    
    // just work with dmt and dpt and current?
}