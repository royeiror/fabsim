cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build graphical interface" ON)

# --- Dependencies ---
# Eigen (header-only)
find_package(Eigen3 REQUIRED)

# tinyobjloader (download + build automatically)
include(FetchContent)
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG master
)
FetchContent_MakeAvailable(tinyobjloader)

# If GUI is enabled, also fetch GL stuff
if (BUILD_GUI)
    # GLAD
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
    )
    FetchContent_MakeAvailable(glad)

    # GLFW
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest
    )
    FetchContent_MakeAvailable(glfw)
endif()

# --- Source files ---
# Collect *all* .cpp files under src/
file(GLOB_RECURSE FABSIM_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

if(NOT FABSIM_SOURCES)
    message(FATAL_ERROR "No source files found in src/. You must add code before building.")
endif()

# --- Library ---
add_library(fabsim_lib ${FABSIM_SOURCES})
target_include_directories(fabsim_lib PUBLIC include)
target_link_libraries(fabsim_lib PUBLIC Eigen3::Eigen tinyobjloader)


# --- Optional GUI binary ---
if (BUILD_GUI)
    add_executable(fabsim_gui app/main.cpp)

    target_include_directories(fabsim_gui PUBLIC include)

    target_link_libraries(fabsim_gui
        PRIVATE
            fabsim_lib
            glad
            glfw
    )

    # Windows needs this
    if (MSVC)
        target_compil_
