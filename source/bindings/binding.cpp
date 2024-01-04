#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../relativity/include/vec2.hpp"
#include "../relativity/include/vel2.hpp"
#include "../relativity/include/vec3.hpp"
#include "../relativity/include/worldline.hpp"
#include "../relativity/include/pointworldline.hpp"
#include "../relativity/include/integrator.hpp"

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

    py::class_<Frame>(m, "Frame")
        .def(py::init<>());

    py::class_<Worldline>(m, "Worldline")
        .def_readwrite("ptime", &Worldline::ptime)
        .def_readwrite("vel", &Worldline::vel)
        .def_readwrite("current", &Worldline::current)
        .def("dt_step", &Worldline::dt_step)
        .def("dv_step", &Worldline::dv_step);

    py::class_<PointWorldline>(m, "PointWorldline")
        .def(py::init<Frame, const vec2>())
        .def_readwrite("ptime", &Worldline::ptime)
        .def_readwrite("vel", &Worldline::vel)
        .def_readwrite("current", &Worldline::current)
        .def("event_at_ptime", &PointWorldline::event_at_ptime)
        .def("vel_at_ptime", &PointWorldline::vel_at_ptime)
        .def("dt_step", &Worldline::dt_step)
        .def("dv_step", &Worldline::dv_step);

    py::class_<Integrator>(m, "Integrator")
        .def(py::init<Frame>())
        .def("add_worldline", &Integrator::add_worldline)
        .def("step", &Integrator::step);
}
