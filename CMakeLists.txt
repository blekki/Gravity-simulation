cmake_minimum_required(VERSION 3.15)

set(BUILD_DIR build)
set(SOURCES
    # start point (main)
    src/simulation.cpp
    # structures
    src/struct/coord.cpp
    # physics logic
    src/cloud/cloud.cpp
    src/cloud/cloud2d.cpp
    src/cloud/cloud3d.cpp
    src/cloud/cloudFactory.cpp
    src/cloud/physics/particle.cpp
    src/cloud/physics/node.cpp
    # other
    src/window/window.cpp
    src/timer/timer.cpp
)

# add fast way include headers
add_library(headers INTERFACE)
target_include_directories(headers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cloud
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cloud/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/struct
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window
    ${CMAKE_CURRENT_SOURCE_DIR}/src/camera
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timer
)

# compilation rules
project(simulation)
set(CMAKE_CXX_FLAGS "-O0 -g2")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BUILD_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC headers GLEW glfw GL GLU)