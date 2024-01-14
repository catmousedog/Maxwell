#include "../include/rigidbody.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

RigidBody::RigidPoint::RigidPoint(const vec2& mpos, const vec2& ppos) : Point(mpos), ppos(ppos) {}

RigidBody::RigidBody(const Frame& frame, const vec2& ref_mpos, const vel2& vel_init, const vec2& ref_accel)
    : frame(frame), ref_mpos(ref_mpos), vel_init(vel_init), ref_accel(ref_accel)
{}

RigidBody::~RigidBody()
{
    for (size_t i = 0; i < rigid_points.size(); i++) delete rigid_points[i];
}

Point* RigidBody::addPoint(const vec2& ppos)
{
    if (setup_done) throw std::logic_error("RigidBody has already been setup, Points can no longer be added");

    // WIP CONTRACTION
    vec2 mpos = vel_init.contract(ppos);  // mainframe position

    RigidPoint* rp = new RigidPoint(ref_mpos + mpos, ppos);
    rigid_points.push_back(rp);
    return rp;
}

void RigidBody::setup()
{
    Body::setup();

    ref_time = frame.time;
    updateAccel(ref_accel);

    scalar A = ref_accel.mag();
    for (auto* rp : rigid_points)
    {
        scalar u;
        scalar a = rp->scheduled_accels.front().second.mag();  // scheduled accel of this point
        if (A != 0)
            u = rp->vel.mag * rp->vel.gamma * a / A;
        else
            u = rp->vel.mag * rp->vel.gamma;  // a/A = 1

        scalar v = u / sqrt(1 + u * u);
        rp->vel = v * vel_init.dir;
    }
    setup_done = true;
}

void RigidBody::step(scalar dmt)
{
    for (auto* rp : rigid_points)
    {
        if (rp->scheduled_accels.size() > 0)
        {
            const auto& scheduled = rp->scheduled_accels.front();
            if (frame.time >= scheduled.first)  // acceleration needs to change
            {
                rp->accel = scheduled.second;
                rp->scheduled_accels.pop();
            }
        }
        rp->step(dmt);
    }
}

bool RigidBody::updateAccel(const vec2& accel)
{
    // if (!setup_done)
    //     throw std::logic_error("Integrator needs to be started before changing the acceleration of the RigidBody.");

    if (ref_time > frame.time) return false;  // ref point is busy
    // if (accel == ref_accel) return false;     // useless update

    // // find most 'past' point, this point will need to accelerate first
    // // this is the point which is furthest in the opposite direction of the velocity
    scalar min_u = std::numeric_limits<scalar>::max();
    RigidPoint* first;
    for (auto* rp : rigid_points)
    {
        // only the smallest matters, the magnitude is not used
        scalar u = rp->vel * rp->ppos;
        if (u < min_u)
        {
            min_u = u;
            first = rp;
        }
    }

    // calc acceleration for all points (and ref) and put them in their schedule
    scalar A;
    vec2 dir = accel.normalised(A);
    scalar D = 1 / A;

    // calc ref_time
    vec3 now = first->ppos.boosted(first->vel);  // the now event from first's frame
    ref_time = frame.time - now.t;               // time at which ref needs to start accelerating

    for (auto* rp : rigid_points)
    {
        // will probably have to change ppos to normal pos as the RigidBody can rotate
        // or rotate ppos?

        vec2 first_ppos = rp->ppos - first->ppos;   // relative proper position
        vec3 now = first_ppos.boosted(first->vel);  // the now event from first's frame
        scalar time = frame.time + now.t;           // time at which point needs to start accelerating

        scalar d = rp->ppos * dir;
        if (d < -D)
        {
            printf("%f %f\n", rp->ppos.x, rp->ppos.y);
            printf("%f %f\n", dir.x, dir.y);
            printf("BEYOND HORIZON\n");
            // BEYOND RINDLER HORIZON
        }
        scalar a = 0 ? A == 0 : 1 / (D + d);                       // Rindler acceleration A * D/(D+d) if A is not 0
        rp->scheduled_accels.push(std::make_pair(time, dir * a));  // schedule the acceleration
    }

    return true;
}

std::vector<Point*> RigidBody::getPoints()
{
    std::vector<Point*> test;
    for (auto* rp : rigid_points) test.push_back(rp);
    return test;
}