
project(tests)

find_package(Catch2 REQUIRED)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}" SUFFIX ".exe")

target_link_libraries(${PROJECT_NAME} ${RELAT_LIB_PATH} Catch2::Catch2)

# include(Catch)
# catch_discover_tests(${PROJECT_NAME})
