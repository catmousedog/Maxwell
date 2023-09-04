#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vel2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/worldline.hpp"
#include "../relativity/include/pointworldline.hpp"

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
        .def(py::init<const vel2 &>())
        .def("mag", &vel2::mag)
        .def("gamma", &vel2::gamma)
        .def("igamma", &vel2::igamma)
        .def("vx", &vel2::vx)
        .def("vy", &vel2::vy)
        .def(py::self += py::self);

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y);

    py::class_<Frame>(m, "Frame")
        .def(py::init<>());

    py::class_<Worldline>(m, "Worldline")
        .def_readwrite("vel", &Worldline::vel);

    py::class_<PointWorldline>(m, "PointWorldline")
        .def(py::init<Frame>())
        .def_readwrite("vel", &Worldline::vel)
        .def("event_at_ptime", &PointWorldline::event_at_ptime);
}
