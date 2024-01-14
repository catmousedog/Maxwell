#include "../relativity/include/frame.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/rigidbody.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <random>

#define SQUARE(X) ((X) * (X))

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

scalar rindler_tau(scalar v, scalar g, scalar a, scalar T)
{
    return log((T * a + g * v + sqrt(SQUARE(T * a) + 2 * T * a * g * v + SQUARE(g))) / (g * (v + 1))) / a;
}

scalar rindler_x(scalar v, scalar g, scalar a, scalar tau, scalar x)
{
    return g / (2 * a) * ((1 + v) * exp(a * tau) + (1 - v) * exp(-a * tau) - 2) + x;
}

scalar rindler_t(scalar v, scalar g, scalar a, scalar tau)
{
    return g / (2 * a) * ((1 + v) * exp(a * tau) - (1 - v) * exp(-a * tau) - 2 * v);
}

TEST_CASE("Integrator")
{

    SECTION("Rindler")
    {
        Frame frame;

        scalar T = 10;
        scalar dt = 0.01;
        // initial conditions //
        scalar x1 = 0;
        scalar v1 = 0.;
        scalar a1 = 1;
        CAPTURE(x1);
        CAPTURE(v1);
        CAPTURE(a1);
        ////////////////////////
        scalar g1 = 1 / sqrt(1 - v1 * v1);

        Point point(vec3(0, x1, 0), vel2(v1, 0), vec2(a1, 0));

        Integrator integrator(frame);
        integrator.addBody(&point);
        for (scalar t = 0; t < T; t += dt)
        {
            scalar tau1 = rindler_tau(v1, g1, a1, t);

            scalar X1 = rindler_x(v1, g1, a1, tau1, x1);

            CAPTURE(t);
            REQUIRE(point.pos.t == Approx(t).epsilon(0.01).margin(0.01));
            REQUIRE(point.pos.x == Approx(X1).epsilon(0.01).margin(0.01));
            integrator.step(dt);
        }
    }

    SECTION("RigidBody")
    {
        Frame frame;

        scalar T = 10;
        scalar dt = 0.01;
        // initial conditions //
        scalar x1 = 0;
        scalar v1 = 0.0;
        scalar a1 = .2;
        scalar d2 = 1;
        CAPTURE(x1);
        CAPTURE(v1);
        CAPTURE(a1);
        CAPTURE(d2);
        ////////////////////////
        scalar g1 = 1 / sqrt(1 - v1 * v1);
        scalar x2 = x1 + d2 / g1;
        scalar a2 = 1 / (1 / a1 + d2);
        scalar u2 = v1 * g1 * a2 / a1;
        scalar v2 = u2 / sqrt(1 + u2 * u2);
        scalar g2 = 1 / sqrt(1 - v2 * v2);

        CAPTURE(x2);
        CAPTURE(v2);
        CAPTURE(a2);

        vel2 o(0.5, 0);
        vel2 o2(0, -0.5);
        vel2 b = o.boosted(o2);
        vel2 b2 = o2.boosted(o);

        RigidBody body(frame, vec2(x1, 0), vel2(v1, 0), vec2(a1, 0));
        scalar l = 1;
        Point* point1 = body.addPoint(vec2(-l, -l));
        Point* point2 = body.addPoint(vec2(-l, l));
        Point* point3 = body.addPoint(vec2(l, l));
        Point* point4 = body.addPoint(vec2(l, -l));

        Integrator integrator(frame);
        integrator.addBody(&body);
        integrator.setup();
        int i = 0;
        for (scalar t = 0; t < T; t += dt)
        {
            // scalar tau1 = rindler_tau(v1, g1, a1, t);
            // scalar tau2 = rindler_tau(v2, g2, a2, t);

            // scalar X1 = rindler_x(v1, g1, a1, tau1, x1);
            // scalar X2 = rindler_x(v2, g2, a2, tau2, x2);

            if (point1->vel.x > .5) body.updateAccel(vec2(0, -1));

            CAPTURE(t);
            // REQUIRE(point1->pos.t == Approx(t).epsilon(0.01).margin(0.01));
            // REQUIRE(point1->pos.x == Approx(X1).epsilon(0.01).margin(0.01));
            // REQUIRE(point2->pos.t == Approx(t).epsilon(0.01).margin(0.01));
            // REQUIRE(point2->pos.x == Approx(X2).epsilon(0.01).margin(0.01));
            integrator.step(dt);
        }
    }
}
