#define CATCH_CONFIG_MAIN

#include <vector>

#include <catch.hpp>

#include "../relativity/include/Event.h"

TEST_CASE("3 VEC")
{
    SECTION("constructor")
    {
        Position position(1.0, 2.0, 3.0);

        REQUIRE(position.t == (decimal)1.0);
        REQUIRE(position.x == (decimal)2.0);
        REQUIRE(position.y == (decimal)3.0);
    }
}