cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Eigen is header-only. Just include the path.
include_directories(${PROJECT_SOURCE_DIR}/deps/eigen)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Core sources
set(FABSIM_SOURCES
    src/ElasticRod.cpp
    src/HingeElement.cpp
    src/LocalFrame.cpp
    src/RodStencil.cpp
    src/geometry.cpp
)

add_library(fabsim_lib ${FABSIM_SOURCES})

# CLI executable
add_executable(fabsim src/main.cpp)
target_link_libraries(fabsim fabsim_lib)

# GUI support
option(BUILD_GUI "Build GUI application" OFF)

if(BUILD_GUI)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(imgui CONFIG REQUIRED)

    add_executable(fabsim_gui
        gui/main.cpp
        gui/viewer.cpp
        gui/viewer.h
    )

    target_link_libraries(fabsim_gui
        fabsim_lib
        OpenGL::GL
        glfw
        imgui::imgui
    )
endif()

