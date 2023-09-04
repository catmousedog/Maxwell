#include <catch2/catch.hpp>

#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vel2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/frame.hpp"
#include "../relativity/include/pointworldline.hpp"

#include <iostream>

TEST_CASE("vec")
{
    SECTION("vec3")
    {
        vec3 v(1.0, 2.0, 3.0);

        REQUIRE(v.t == (scalar)1.0);
        REQUIRE(v.x == (scalar)2.0);
        REQUIRE(v.y == (scalar)3.0);
    }

    SECTION("vec2")
    {
        vec2 v(2.0, 3.0);

        REQUIRE(v.x == (scalar)2.0);
        REQUIRE(v.y == (scalar)3.0);
    }

    SECTION("vel2")
    {
        vel2 v = vel2(0, .99);
        vel2 boost = vel2(0.99, 0);
        vel2 bv = v + boost;
        
        REQUIRE(bv.vx() == Approx(0.99));
        REQUIRE(bv.vy() == Approx(0.99 * v.igamma()));
        REQUIRE(bv.mag() == Approx(0.999801975393));
    }
}
