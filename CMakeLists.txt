cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Dependencies
find_package(Eigen3 3.3 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${EIGEN3_INCLUDE_DIRS}
)

# Collect source files
set(FABSIM_SOURCES
    src/ElasticRod.cpp
    src/HingeElement.cpp
    src/LocalFrame.cpp
    src/RodStencil.cpp
    src/geometry.cpp        # ✅ THIS WAS MISSING
)

add_library(fabsim_lib ${FABSIM_SOURCES})

target_link_libraries(fabsim_lib Eigen3::Eigen)

# Executable (CLI)
add_executable(fabsim src/main.cpp)
target_link_libraries(fabsim fabsim_lib)

# GUI Support
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

