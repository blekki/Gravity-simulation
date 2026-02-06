cmake_minimum_required(VERSION 3.15)
project(simulation)
set(CMAKE_CXX_FLAGS "-O0 -g2")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BUILD_DIR})

# various variables
set(BUILD_DIR build)
set(LIBS GLEW glfw GL GLU)
set(SOURCES
    # start point (main):
    src/simulation.cpp
    # structures:
    src/struct/coord.cpp
    # physics logic:
    src/physics/cloud.cpp
    src/physics/particle.cpp
    src/physics/node.cpp
    # other:
    src/window/window.cpp
    src/timer/timer.cpp
)

# create static lib
add_library(SUBDIRS_INTERFACE INTERFACE)
target_include_directories(SUBDIRS_INTERFACE INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/struct
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window
    ${CMAKE_CURRENT_SOURCE_DIR}/src/camera
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timer
)
add_library(static_lib STATIC ${SOURCES})   # uses for fast way compile unit_tests
target_link_libraries(static_lib PUBLIC SUBDIRS_INTERFACE)

# project compilation
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC static_lib ${LIBS})

# other
enable_testing()
add_subdirectory(tests)