#include <pybind11/pybind11.h>

#include "../relativity/include/Event.h"

namespace py = pybind11;

int add(int a, int b)
{
    return a + b;
}

PYBIND11_MODULE(relatpy, m)
{
    m.doc() = "pybind11 example plugin";

    m.def("add", &add, "A function that adds two numbers");

    py::class_<Position>(m, "Position")
        .def(py::init<decimal, decimal, decimal>())
        .def_readwrite("t", &Position::t)
        .def_readwrite("x", &Position::x)
        .def_readwrite("y", &Position::y);
}
