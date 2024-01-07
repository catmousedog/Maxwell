#include "../relativity/include/frame.hpp"
#include "../relativity/include/pointpoint.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <random>

TEST_CASE("vec")
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

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

        // boost with itself should be v_new = 2v / (1+v²)
        double vx = uniform(gen);
        double vy = sqrt(1 - vx * vx);
        v = vel2(vx * 0.5, vy * 0.5);
        bv = v.boosted(v);
        double g = 1 / (1 + v.mag2());

        // same direction
        REQUIRE(v.dir().x == Approx(bv.dir().x));
        REQUIRE(v.dir().y == Approx(bv.dir().y));

        REQUIRE(bv.vx() == Approx(2 * v.vx() * g));
        REQUIRE(bv.vy() == Approx(2 * v.vy() * g));
        REQUIRE(bv.mag() == Approx(2 * v.mag() * g));
    }

    SECTION("boost")
    {
        vel2 v(0, 0);
        vec3 e(1, 2, 3);

        vec3 b = e.boosted(v);
        REQUIRE(b == e);
        REQUIRE(&b != &e);

        vec3& d = e.boost(v);
        REQUIRE(d == e);
        REQUIRE(&d == &e);
    }
}

TEST_CASE("worldline")
{
    SECTION("point")
    {
        // Frame mainframe;
        // PointWorldline point(mainframe);

        // point.event_at_ptime(0.);
        // point.vel_at_ptime(0.);
        // point.mtime_step(1.0);
    }
}
