#include <pybind11/pybind11.h>

#include "../relativity/include/vec.hpp"
#include "../relativity/include/worldline.hpp"
#include "../relativity/include/pointworldline.hpp"

namespace py = pybind11;

int add(int a, int b)
{
    return a + b;
}

PYBIND11_MODULE(relatpy, m)
{
    m.doc() = "pybind11 example plugin";

    m.def("add", &add, "A function that adds two numbers");

    py::class_<vec3>(m, "vec3")
        .def(py::init<>())
        .def(py::init<scalar, scalar, scalar>())
        .def_readwrite("t", &vec3::t)
        .def_readwrite("x", &vec3::x)
        .def_readwrite("y", &vec3::y);

    py::class_<Frame>(m, "Frame")
        .def(py::init<>());

    py::class_<Worldline>(m, "Worldline");

    py::class_<PointWorldline>(m, "PointWorldline")
        .def(py::init<Frame>())
        .def("integrate", &PointWorldline::integrate);
}
