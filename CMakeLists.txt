cmake_minimum_required(VERSION 3.22)

project(root)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PYTHON_DIR ${ROOT_DIR}/python)
set(SOURCE_DIR ${ROOT_DIR}/source)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})


add_subdirectory("source")