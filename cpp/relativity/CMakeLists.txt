project(relativity)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

set(RELAT_LIB_PATH ${CMAKE_BINARY_DIR}/relativity/relativity.so PARENT_SCOPE)