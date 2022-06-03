
cmake_minimum_required(VERSION 3.10)

find_package(OpenGL REQUIRED)

include_directories(include)
#set( SOURCES ../src/Viewer.cc )

set( CMAKE_CXX_FLAGS "-g")

add_executable(tests ./viewer_primitives.cc ../src/Viewer.cc)

target_link_libraries(tests GL GLU glut GLEW)

