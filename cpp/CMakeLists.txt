cmake_minimum_required(VERSION 3.22)

project(total_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_subdirectory("relativity")

add_subdirectory("tests")

add_subdirectory("bindings")
