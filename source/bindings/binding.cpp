#include "../relativity/include/body.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include "../relativity/include/vel3.hpp"
#include <pybind11/complex.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

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
        .def("boosted", &vec2::boosted);

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def(py::init<const vec3&>())
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
        .def("boosted", &vec3::boosted);

    py::class_<vel2, vec2>(m, "vel2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def(py::init<const vel2&>())
        .def_readwrite("x", &vel2::x)
        .def_readwrite("y", &vel2::y)
        .def_readwrite("mag", &vel2::mag)
        .def_readwrite("mag2", &vel2::mag2)
        .def_readwrite("gamma", &vel2::gamma)
        .def_readwrite("igamma", &vel2::igamma)
        .def("contract", &vel2::contract);

    py::class_<vel3, vec3>(m, "vel3")
        .def(py::init<>())
        .def(py::init<const vel2&>())
        .def(py::init<scalar, scalar, scalar>())
        .def_readwrite("t", &vel3::t)
        .def_readwrite("x", &vel3::x)
        .def_readwrite("y", &vel3::y)
        .def_readwrite("v", &vel3::v)
        .def("mag", &vel3::mag)
        .def("mag2", &vel3::mag2)
        .def("normalise", py::overload_cast<>(&vel3::normalise))
        .def("normalise", py::overload_cast<scalar&>(&vel3::normalise))
        .def("normalised", py::overload_cast<>(&vel3::normalised, py::const_))
        .def("normalised", py::overload_cast<scalar&>(&vel3::normalised, py::const_));

    py::class_<Frame>(m, "Frame").def(py::init<>());

    py::class_<Point>(m, "Point")
        .def(py::init<const vec3&, const vel2&, const vec2&>())
        .def_readwrite("pos", &Point::pos)
        .def_readwrite("accel", &Point::accel)
        .def_readwrite("ptime", &Point::ptime);

    py::class_<Body, Point>(m, "Body")
        .def(py::init<const vec3&, const vel2&, const vec2&>())
        .def("addPoint", &Body::addPoint)
        .def("getPoints", &Body::getPoints, py::return_value_policy::reference);

    py::class_<Integrator>(m, "Integrator")
        .def(py::init<Frame>())
        .def("addPoint", &Integrator::addPoint)
        .def("step", &Integrator::step)
        .def("getPoints", &Integrator::getPoints, py::return_value_policy::reference);
}
