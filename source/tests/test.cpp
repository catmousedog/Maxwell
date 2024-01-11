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

scalar rand_scalar(scalar start = 0.0, scalar end = 1.0)
{
    return uniform(gen) * (end - start) + start;
}

vec2 rand_vec2()
{
    scalar x = rand_scalar();
    scalar y = sqrt(1 - x * x);
    return vec2(x, y);
}

vec3 rand_vec3()
{
    scalar x = rand_scalar();
    scalar y = sqrt(1 - x * x);
    return vec3(0, x, y);
}

vel2 rand_vel2(scalar v)
{
    scalar vx = rand_scalar();
    scalar vy = sqrt(1 - vx * vx);
    return vel2(vx * v, vy * v);
}

TEST_CASE("vec")
{
    SECTION("vec2")
    {
        vec2 v(2.0, 3.0);

        REQUIRE(v.x == (scalar)2.0);
        REQUIRE(v.y == (scalar)3.0);
    }

    SECTION("vec3")
    {
        vec3 v(1.0, 2.0, 3.0);

        REQUIRE(v.t == (scalar)1.0);
        REQUIRE(v.x == (scalar)2.0);
        REQUIRE(v.y == (scalar)3.0);
    }

    SECTION("vel2")
    {
        vel2 u = vel2(0, .99);
        vel2 v = vel2(0.99, 0);
        vel2 bu = u.boosted(v);

        REQUIRE(bu.x == Approx(0.99));
        REQUIRE(bu.y == Approx(0.99 * u.igamma));
        REQUIRE(bu.mag == Approx(0.999801975393));

        // boost with itself should be v_new = 2v / (1+v²)
        u = rand_vel2(0.5);
        bu = u.boosted(u);
        scalar g = 1 / (1 + u.mag2);

        // same direction
        REQUIRE(u.dir.x == Approx(bu.dir.x));
        REQUIRE(u.dir.y == Approx(bu.dir.y));

        REQUIRE(bu.x == Approx(2 * u.x * g));
        REQUIRE(bu.y == Approx(2 * u.y * g));
        REQUIRE(bu.mag == Approx(2 * u.mag * g));
    }

    SECTION("vel3") {}

    SECTION("boost") {}
}

TEST_CASE("Integrator")
{
    SECTION("Rindler")
    {
        Frame frame;

        scalar dt = 0.1;
        // initial conditions //
        scalar x1 = 0;
        scalar v1 = 0.;
        scalar a1 = 1;
        CAPTURE(x1);
        CAPTURE(v1);
        CAPTURE(a1);
        ////////////////////////

        Point point(vec3(0, x1, 0), vel2(v1, 0), vec2(a1, 0));

        Integrator integrator(frame);
        integrator.addPoint(&point);
        for (scalar t = 0; t < 10; t += dt)
        {
            scalar tau1 = point.pos.t;

            scalar X1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) + (1 - v1) * exp(-a1 * tau1) - 2) + x1;
            scalar T1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) - (1 - v1) * exp(-a1 * tau1) - 2 * v1);

            CAPTURE(t);
            CAPTURE(tau1);
            // REQUIRE(point.t == Approx(T1).epsilon(0.01).margin(0.01));
            // REQUIRE(point.x == Approx(X1).epsilon(0.01).margin(0.01));
            integrator.step(dt);
        }
    }

    SECTION("Body")
    {
        // Frame mainframe;

        // scalar dt = 0.01;
        // // initial conditions //
        // scalar x1 = 0;
        // scalar v1 = -0.9;
        // scalar g1 = 1 / sqrt(1 - v1 * v1);
        // scalar a1 = 1;
        // scalar d2 = 1;
        // CAPTURE(x1);
        // CAPTURE(v1);
        // CAPTURE(g1);
        // CAPTURE(a1);
        // CAPTURE(d2);
        // ////////////////////////
        // scalar x2 = x1 + d2 / g1;
        // scalar a2 = 1 / (1 / a1 + d2);
        // scalar u2 = a2 / a1 * v1 * g1;
        // scalar v2 = u2 / (1 + u2 * u2);
        // CAPTURE(x2);
        // CAPTURE(v2);
        // CAPTURE(a2);

        // Body body(mainframe, vec3(0, x1, 0));
        // body.accel = vec2(a1, 0);
        // body.U = vel2(v1, 0);
        // body.addPoint(vec2(d2, 0));
        // Point& point = *body.getPoints()[0];

        // Integrator integrator(mainframe);
        // integrator.addPoint(&body);
        // for (scalar t = 0; t < 10; t += dt)
        // {
        //     scalar tau1 = body.ptime;
        //     scalar tau2 = point.ptime;

        //     scalar X1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) + (1 - v1) * exp(-a1 * tau1) - 2) + x1;
        //     scalar T1 = 1 / (2 * a1) * ((1 + v1) * exp(a1 * tau1) - (1 - v1) * exp(-a1 * tau1) - 2 * v1);
        //     scalar X2 = 1 / (2 * a2) * ((1 + v2) * exp(a2 * tau2) + (1 - v2) * exp(-a2 * tau2) - 2) + x2;
        //     scalar T2 = 1 / (2 * a2) * ((1 + v2) * exp(a2 * tau2) - (1 - v2) * exp(-a2 * tau2) - 2 * v2);

        //     CAPTURE(t);
        //     CAPTURE(tau1);
        //     CAPTURE(tau2);
        //     REQUIRE(body.t == Approx(T1).epsilon(0.01).margin(0.01));
        //     REQUIRE(body.x == Approx(X1).epsilon(0.01).margin(0.01));
        //     REQUIRE(point.t == Approx(T2).epsilon(0.01).margin(0.01));
        //     REQUIRE(point.x == Approx(X2).epsilon(0.01).margin(0.01));
        //     integrator.step(dt);
        // }
    }
}
