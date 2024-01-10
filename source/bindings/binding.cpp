#include "../relativity/include/body.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
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
        .def_readwrite("x", &vec2::x)
        .def_readwrite("y", &vec2::y);

    py::class_<vel2, vec2>(m, "vel2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def(py::init<const vel2&>())
        .def_readwrite("mag", &vel2::mag)
        .def_readwrite("mag2", &vel2::mag2)
        .def_readwrite("gamma", &vel2::gamma)
        .def_readwrite("igamma", &vel2::igamma)
        .def("boost_vel", &vel2::boost)
        .def("boosted_vel", &vel2::boosted);

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y)
        .def("pos", &vec3::pos)
        .def("boost_vec", &vec3::boost)
        .def("boosted_vec", &vec3::boosted);

    py::class_<Frame>(m, "Frame").def(py::init<>());

    py::class_<Point, vec3>(m, "Point")
        .def(py::init<Frame>())
        .def(py::init<Frame, vec3>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y)
        .def_readwrite("ptime", &Point::ptime)
        .def_readwrite("vel", &Point::vel)
        .def_readwrite("accel", &Point::accel)
        .def("step", &Point::step);

    py::class_<Body, Point>(m, "Body")
        .def(py::init<Frame, vec3>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y)
        .def("addPoint", &Body::addPoint)
        .def("step", &Body::step)
        .def("getPoints", &Body::getPoints, py::return_value_policy::reference);

    py::class_<Integrator>(m, "Integrator")
        .def(py::init<Frame>())
        .def("addPoint", &Integrator::addPoint)
        .def("step", &Integrator::step)
        .def("getPoints", &Integrator::getPoints, py::return_value_policy::reference);
}
