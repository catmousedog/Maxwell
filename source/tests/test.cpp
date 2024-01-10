#include "../relativity/include/body.hpp"
#include "../relativity/include/frame.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> uniform(0.0, 1.0);

double randd(double start = 0.0, double end = 1.0)
{
    return uniform(gen) * (end - start) + start;
}

vec2 randd2()
{
    double x = randd();
    double y = sqrt(1 - x * x);
    return vec2(x, y);
}

vec3 randd3()
{
    double x = randd();
    double y = sqrt(1 - x * x);
    return vec3(0, x, y);
}

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

        REQUIRE(bv.x == Approx(0.99));
        REQUIRE(bv.y == Approx(0.99 * v.igamma));
        REQUIRE(bv.mag == Approx(0.999801975393));

        // boost with itself should be v_new = 2v / (1+v²)
        v = vel2(0.5 * randd2());
        bv = v.boosted(v);
        double g = 1 / (1 + v.mag2);

        // same direction
        REQUIRE(v.dir.x == Approx(bv.dir.x));
        REQUIRE(v.dir.y == Approx(bv.dir.y));

        REQUIRE(bv.x == Approx(2 * v.x * g));
        REQUIRE(bv.y == Approx(2 * v.y * g));
        REQUIRE(bv.mag == Approx(2 * v.mag * g));
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

TEST_CASE("Integrator")
{
    SECTION("Rindler")
    {
        Frame mainframe;

        double dt = 0.01;
        double x0 = randd();
        double t0 = randd();
        double v = randd(-1, 1);
        double g = 1 / sqrt(1 - v * v);
        double a = randd(-1, 1);
        CAPTURE(x0);
        CAPTURE(t0);
        CAPTURE(v);
        CAPTURE(g);
        CAPTURE(a);

        Point point(mainframe, vec3(t0, x0, 0));
        point.vel = vel2(v, 0);
        point.accel = vec2(a, 0);

        Integrator integrator(mainframe);
        integrator.addPoint(&point);
        for (double t = 0; t < 10; t += dt)
        {
            double tau = point.ptime;

            double X = g / (2 * a) * ((1 + v) * exp(a * tau) + (1 - v) * exp(-a * tau) - 2) + x0;
            double T = g / (2 * a) * ((1 + v) * exp(a * tau) - (1 - v) * exp(-a * tau) - 2 * v) + t0;
            CAPTURE(t);
            REQUIRE(point.t == Approx(T).epsilon(0.25).margin(0.05));
            REQUIRE(point.x == Approx(X).epsilon(0.25).margin(0.05));
            integrator.step(dt);
        }
    }
}
