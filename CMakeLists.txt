cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build graphical interface" ON)

include(FetchContent)

# --- Eigen ---
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# --- tinyobjloader (PINNED WORKING TAG) ---
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# --- GUI dependencies ---
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
        GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)
endif()

# --- Source files ---
file(GLOB_RECURSE FABSIM_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

if(NOT FABSIM_SOURCES)
    message(FATAL_ERROR "No source files found in src/. Add .cpp files to src/.")
endif()

# --- Main Core Library ---
add_library(fabsim_lib ${FABSIM_SOURCES})
target_include_directories(fabsim_lib PUBLIC include)
target_link_libraries(fabsim_lib PUBLIC Eigen3::Eigen tinyobjloader)

# --- GUI Executable ---
if (BUILD_GUI)
    add_executable(fabsim_gui app/main.cpp)
    target_include_directories(fabsim_gui PUBLIC include)
    target_link_libraries(fabsim_gui PRIVATE fabsim_lib glad glfw)

    if(MSVC)
        target_compile_definitions(fabsim_gui PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()
endif()

message(STATUS "BUILD_GUI = ${BUILD_GUI}")
