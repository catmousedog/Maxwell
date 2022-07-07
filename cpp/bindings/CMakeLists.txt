project(module)

find_package(pybind11 REQUIRED)

file(GLOB SOURCES "../relativity/src/*.cpp")
file(GLOB HEADERS "../relativity/include/*.h")
file(GLOB BINDINGS "*.cpp")

pybind11_add_module(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${BINDINGS})