
cmake_minimum_required(VERSION 3.10)
project(tinydim VERSION 0.1)

find_package(OpenGL REQUIRED)
find_package(glut REQUIRED)

include_directories(include)
set( SOURCES src/Viewer.cc )

set( CMAKE_CXX_FLAGS "-g")

add_executable(tinydim test/test.cc ${SOURCES})

target_link_libraries(tinydim GL GLU glut GLEW)

