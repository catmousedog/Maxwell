project(relatpy)

find_package(pybind11 REQUIRED)

file(GLOB SOURCES "../relativity/src/*.cpp")
file(GLOB HEADERS "../relativity/include/*.hpp")
file(GLOB BINDINGS "*.cpp")

pybind11_add_module(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${BINDINGS})

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PYTHON_DIR})
