project(relativity)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

set(RELAT_LIB_PATH ${BIN_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.so PARENT_SCOPE)
