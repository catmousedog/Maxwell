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
        vel2 bv = v.boosted(boost);

        REQUIRE(bv.vx() == Approx(0.99));
        REQUIRE(bv.vy() == Approx(0.99 * v.igamma()));
        REQUIRE(bv.mag() == Approx(0.999801975393));
    }

    SECTION("boost")
    {
        vel2 v(0, 0);
        vec3 e(1, 2, 3);

        vec3 b = e.boosted(v);
        REQUIRE(b == e);
        REQUIRE(&b != &e);

        vec3 &d = e.boost(v);
        REQUIRE(d == e);
        REQUIRE(&d == &e);
    }
}

TEST_CASE("worldline")
{
    SECTION("point")
    {
        Frame mainframe;
        PointWorldline point(mainframe);

        point.event_at_ptime(0.);
        point.vel_at_ptime(0.);
        point.mtime_step(1.0);
    }
}
