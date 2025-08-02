cmake_minimum_required(VERSION 3.14)

project(simulation)

add_executable(${PROJECT_NAME} simulation.cpp window.cpp 
                               cloud.cpp cloud2d.cpp cloud3d.cpp cloudFactory.cpp
                               particle.cpp node.cpp coord.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW glfw GL GLU)

SET(CMAKE_CXX_FLAGS "-O0 -g2")
SET(CMAKE_C_FLAGS "-O0 -g2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")