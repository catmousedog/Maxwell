#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../relativity/include/vec.hpp"

TEST_CASE("3 VEC")
{
    SECTION("constructor")
    {
        vec3 v(1.0, 2.0, 3.0);

        REQUIRE(v.t == (scalar)1.0);
        REQUIRE(v.x == (scalar)2.0);
        REQUIRE(v.y == (scalar)3.0);
    }
}
