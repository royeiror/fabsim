cmake_minimum_required(VERSION 3.10)
project(fabsim)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ----------------------------
# Eigen
# ----------------------------
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# ----------------------------
# tinyobjloader
# ----------------------------
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# ----------------------------
# GLAD
# ----------------------------
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.4
)
FetchContent_MakeAvailable(glad)

# GLAD library target (correct path for GLAD v2.x)
add_library(glad_lib
    ${glad_SOURCE_DIR}/src/gl.c
)
target_include_directories(glad_lib PUBLIC
    ${glad_SOURCE_DIR}/include
)

# ----------------------------
# GLFW
# ----------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# ----------------------------
# Executable
# ----------------------------
add_executable(fabsim_gui
    app/main.cpp
)

target_include_directories(fabsim_gui PUBLIC
    ${eigen_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
    ${glad_SOURCE_DIR}/include
)

target_link_libraries(fabsim_gui PRIVATE
    glad_lib
    glfw
    OpenGL::GL
)

if (WIN32)
    target_link_libraries(fabsim_gui PRIVATE opengl32)
endif()
