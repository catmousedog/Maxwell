
#include <vector>

#include "Event.h"

class ReferenceFrame
{
private:
    std::vector<Event> events;

public:
    ReferenceFrame();
    ReferenceFrame(ReferenceFrame &frame, vec2 velocity);
};

ReferenceFrame::ReferenceFrame()
{
}

ReferenceFrame::~ReferenceFrame()
{
}
