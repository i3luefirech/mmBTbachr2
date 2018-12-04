cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${X11_INCLUDE_DIRS})
IF(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/cairo")
ENDIF()

add_executable(untitled main.cpp)

target_link_libraries(untitled -L/usr/lib/x86_64-linux-gnu -lX11 -lXfixes -lXrender -lXcomposite -lcairo GL GLU)
