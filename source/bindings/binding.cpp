#include "../relativity/include/body.hpp"
#include "../relativity/include/integrator.hpp"
#include "../relativity/include/point.hpp"
#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/vel2.hpp"
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(relatpy, m)
{
    m.doc() = "pybind11 example plugin";

    py::class_<vec2>(m, "vec2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def_readwrite("x", &vec2::x)
        .def_readwrite("y", &vec2::y);

    py::class_<vel2, vec2>(m, "vel2")
        .def(py::init<>())
        .def(py::init<scalar, scalar>())
        .def(py::init<const vel2&>())
        .def("mag", &vel2::mag)
        .def("gamma", &vel2::gamma)
        .def("igamma", &vel2::igamma)
        .def("vx", &vel2::vx)
        .def("vy", &vel2::vy)
        .def("boost_vel", &vel2::boost)
        .def("boosted_vel", &vel2::boosted);

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y)
        .def("boost_vec", &vec3::boost)
        .def("boosted_vec", &vec3::boosted);

    py::class_<Frame>(m, "Frame").def(py::init<>());

    py::class_<Point>(m, "Point")
        .def(py::init<Frame, vec3>())
        .def_readwrite("ptime", &Point::ptime)
        .def_readwrite("vel", &Point::vel)
        .def_readwrite("current", &Point::current)
        .def("step", &Point::step);

    py::class_<Body, Point>(m, "Body")
        .def(py::init<Frame, vec3>())
        .def_readwrite("ptime", &Point::ptime)
        .def_readwrite("vel", &Point::vel)
        .def_readwrite("current", &Point::current)
        .def("addPoint", &Body::addPoint)
        .def("step", &Body::step);

    py::class_<Integrator>(m, "Integrator")
        .def(py::init<Frame>())
        .def("addPoint", &Integrator::addPoint)
        .def("step", &Integrator::step);
}
