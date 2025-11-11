cmake_minimum_required(VERSION 3.14)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -------------------------
# Fetch Eigen automatically
# -------------------------
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# -------------------------
# GLAD + GLFW
# -------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.4
)
FetchContent_MakeAvailable(glad)

# -------------------------
# ImGui
# -------------------------
add_library(imgui
    3rdparty/imgui/imgui.cpp
    3rdparty/imgui/imgui_demo.cpp
    3rdparty/imgui/imgui_draw.cpp
    3rdparty/imgui/imgui_tables.cpp
    3rdparty/imgui/imgui_widgets.cpp
    3rdparty/imgui/backends/imgui_impl_glfw.cpp
    3rdparty/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    3rdparty/imgui
    3rdparty/imgui/backends
)

# -------------------------
# Fabsim Core Library
# -------------------------
file(GLOB FABSIM_CORE_SRC src/*.cpp)
add_library(fabsim_core ${FABSIM_CORE_SRC})

target_include_directories(fabsim_core PUBLIC
    include
    ${eigen_SOURCE_DIR}
)

target_link_libraries(fabsim_core PUBLIC Eigen3::Eigen)

# -------------------------
# Application Executable
# -------------------------
add_executable(fabsim_app src/main.cpp)

target_link_libraries(fabsim_app PRIVATE
    fabsim_core
    imgui
    glfw
    glad
    opengl32
)
