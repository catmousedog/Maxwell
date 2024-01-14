#include "../relativity/include/body.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/rigidbody.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include <pybind11/complex.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class PyBody : public Body {
public:
    using Body::Body; // Inherit constructors

    std::vector<Point*> getPoints() override {
        PYBIND11_OVERLOAD_PURE(
            std::vector<Point*>,  // Return type
            Body,                // Parent class
            getPoints            // Name of the method in C++
        );
    }
};

PYBIND11_MODULE(relatpy, m)
{
    m.doc() = "relatpy";

    py::class_<vec2>(m, "vec2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def(py::init<const vec2&>())
        .def_readwrite("x", &vec2::x)
        .def_readwrite("y", &vec2::y)
        .def("mag", &vec2::mag)
        .def("mag2", &vec2::mag2)
        .def("normalise", py::overload_cast<>(&vec2::normalise))
        .def("normalise", py::overload_cast<scalar&>(&vec2::normalise))
        .def("normalised", py::overload_cast<>(&vec2::normalised, py::const_))
        .def("normalised", py::overload_cast<scalar&>(&vec2::normalised, py::const_))
        .def("boosted", &vec2::boosted)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= scalar())
        .def(py::self /= scalar())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * scalar())
        .def(py::self / scalar())
        .def(py::self * py::self);

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def(py::init<const vec3&>())
        .def(py::init<const vec2&>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y)
        .def("getPos", &vec3::getPos)
        .def("mag", &vec3::mag)
        .def("mag2", &vec3::mag2)
        .def("normalise", py::overload_cast<>(&vec3::normalise))
        .def("normalise", py::overload_cast<scalar&>(&vec3::normalise))
        .def("normalised", py::overload_cast<>(&vec3::normalised, py::const_))
        .def("normalised", py::overload_cast<scalar&>(&vec3::normalised, py::const_))
        .def("boost", &vec3::boost)
        .def("boosted", &vec3::boosted)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= scalar())
        .def(py::self /= scalar())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * scalar())
        .def(py::self / scalar())
        .def(py::self * py::self);

    py::class_<vel2, vec2>(m, "vel2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def(py::init<const vel2&>())
        .def(py::init<const vec2&>())
        .def_readwrite("x", &vel2::x)
        .def_readwrite("y", &vel2::y)
        .def_readwrite("mag", &vel2::mag)
        .def_readwrite("mag2", &vel2::mag2)
        .def_readwrite("gamma", &vel2::gamma)
        .def_readwrite("igamma", &vel2::igamma)
        .def("contract", &vel2::contract)
        .def("boost", &vel2::boost)
        .def("boosted", &vel2::boosted)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= scalar())
        .def(py::self /= scalar())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * scalar())
        .def(py::self / scalar());

    py::class_<Frame>(m, "Frame").def(py::init<>()).def_readonly("time", &Frame::time);

    py::class_<Body, PyBody>(m, "Body")
        .def("setup", &Body::setup)
        .def("step", &Body::step)
        .def("getPoints", &Body::getPoints);

    py::class_<Point, Body>(m, "Point")
        .def(py::init<const vec3&, const vel2&, const vec2&>())
        .def_readwrite("pos", &Point::pos)
        .def_readwrite("vel", &Point::vel)
        .def_readwrite("accel", &Point::accel)
        .def_readwrite("ptime", &Point::ptime);

    py::class_<RigidBody, Body>(m, "RigidBody")
        .def(py::init<const Frame&, const vec2&, const vel2&, const vec2&>())
        .def("addPoint", &RigidBody::addPoint)
        .def("updateAccel", &RigidBody::updateAccel);

    py::class_<Integrator>(m, "Integrator")
        .def(py::init<Frame&>())
        .def("addBody", &Integrator::addBody)
        .def("setup", &Integrator::setup)
        .def("step", &Integrator::step)
        .def("getBodies", &Integrator::getBodies);
}
