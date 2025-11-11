cmake_minimum_required(VERSION 3.15)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)

# Eigen
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# tinyobjloader (old API that fabsim expects)
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# GLFW
find_package(GLFW3 REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)

# Executable (this replaces the broken src/... paths)
add_executable(fabsim
    app/main.cpp
)

target_include_directories(fabsim PRIVATE
    ${eigen_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
    ${glad_SOURCE_DIR}/include
)

target_link_libraries(fabsim PRIVATE
    glad
    glfw
    OpenGL::GL
    tinyobjloader
)
