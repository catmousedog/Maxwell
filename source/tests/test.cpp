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
std::uniform_real_distribution<scalar> uniform(0.0, 1.0);

scalar randd(scalar start = 0.0, scalar end = 1.0)
{
    return uniform(gen) * (end - start) + start;
}

vec2 randd2()
{
    scalar x = randd();
    scalar y = sqrt(1 - x * x);
    return vec2(x, y);
}

vec3 randd3()
{
    scalar x = randd();
    scalar y = sqrt(1 - x * x);
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
        scalar g = 1 / (1 + v.mag2);

        // same direction
        REQUIRE(v.dir.x == Approx(bv.dir.x));
        REQUIRE(v.dir.y == Approx(bv.dir.y));

        REQUIRE(bv.x == Approx(2 * v.x * g));
        REQUIRE(bv.y == Approx(2 * v.y * g));
        REQUIRE(bv.mag == Approx(2 * v.mag * g));
    }

    SECTION("boost") {}
}

TEST_CASE("Integrator")
{
    SECTION("Rindler")
    {
        Frame mainframe;

        scalar dt = 0.01;
        // initial conditions //
        scalar x1 = 0;
        scalar v1 = 0.;
        scalar a1 = 1;
        CAPTURE(x1);
        CAPTURE(v1);
        CAPTURE(a1);
        ////////////////////////

        Point point(mainframe, vec3(0, x1, 0));
        point.accel = vec2(a1, 0);
        point.vel = vel2(v1, 0);

        Integrator integrator(mainframe);
        integrator.addPoint(&point);
        for (scalar t = 0; t < 10; t += dt)
        {
            scalar tau1 = point.ptime;

            scalar X1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) + (1 - v1) * exp(-a1 * tau1) - 2) + x1;
            scalar T1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) - (1 - v1) * exp(-a1 * tau1) - 2 * v1);

            CAPTURE(t);
            CAPTURE(tau1);
            REQUIRE(point.t == Approx(T1).epsilon(0.01).margin(0.01));
            REQUIRE(point.x == Approx(X1).epsilon(0.01).margin(0.01));
            integrator.step(dt);
        }
    }

    SECTION("Body")
    {
        Frame mainframe;

        scalar dt = 0.01;
        // initial conditions //
        scalar x1 = 0;
        scalar v1 = -0.9;
        scalar g1 = 1 / sqrt(1 - v1 * v1);
        scalar a1 = 1;
        scalar d2 = 1;
        CAPTURE(x1);
        CAPTURE(v1);
        CAPTURE(g1);
        CAPTURE(a1);
        CAPTURE(d2);
        ////////////////////////
        scalar x2 = x1 + d2 / g1;
        scalar a2 = 1 / (1 / a1 + d2);
        scalar u2 = a2 / a1 * v1 * g1;
        scalar v2 = u2 / (1 + u2 * u2);
        CAPTURE(x2);
        CAPTURE(v2);
        CAPTURE(a2);

        Body body(mainframe, vec3(0, x1, 0));
        body.accel = vec2(a1, 0);
        body.vel = vel2(v1, 0);
        body.addPoint(vec2(d2, 0));
        Point& point = *body.getPoints()[0];

        Integrator integrator(mainframe);
        integrator.addPoint(&body);
        for (scalar t = 0; t < 10; t += dt)
        {
            scalar tau1 = body.ptime;
            scalar tau2 = point.ptime;

            scalar X1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) + (1 - v1) * exp(-a1 * tau1) - 2) + x1;
            scalar T1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) - (1 - v1) * exp(-a1 * tau1) - 2 * v1);
            scalar X2 = 1 / (2 * a2) * ((1 + v2) * exp(a2 * tau2) + (1 - v2) * exp(-a2 * tau2) - 2) + x2;
            scalar T2 = 1 / (2 * a2) * ((1 + v2) * exp(a2 * tau2) - (1 - v2) * exp(-a2 * tau2) - 2 * v2);

            CAPTURE(t);
            CAPTURE(tau1);
            CAPTURE(tau2);
            REQUIRE(body.t == Approx(T1).epsilon(0.01).margin(0.01));
            REQUIRE(body.x == Approx(X1).epsilon(0.01).margin(0.01));
            REQUIRE(point.t == Approx(T2).epsilon(0.01).margin(0.01));
            REQUIRE(point.x == Approx(X2).epsilon(0.01).margin(0.01));
            integrator.step(dt);
        }
    }
}
