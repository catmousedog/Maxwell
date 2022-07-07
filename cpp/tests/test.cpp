#define CATCH_CONFIG_MAIN

#include <vector>

#include <catch.hpp>

#include "../relativity/include/Event.h"

TEST_CASE("FindMax")
{
    SECTION("4 = 4")
    {
        Event event(1.0, 1.0, 2.0);
        
        REQUIRE(event.x < event.t);
    }
}