cmake_minimum_required(VERSION 3.14)

project(simulation)

add_executable(${PROJECT_NAME} simulation.cpp cloud.cpp particle.cpp node.cpp xyz_t.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW glfw GL)

SET(CMAKE_CXX_FLAGS "-O0 -g2")
SET(CMAKE_C_FLAGS "-O0 -g2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")