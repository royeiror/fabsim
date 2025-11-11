cmake_minimum_required(VERSION 3.14)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -------------------------
# Fetch Eigen
# -------------------------
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# -------------------------
# Fetch GLFW
# -------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# -------------------------
# Fetch GLAD
# -------------------------
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
    ${glfw_SOURCE_DIR}/include
    ${glad_SOURCE_DIR}/include
    ${glad_BINARY_DIR}/include     # <- FIX #1
)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)  # <- FIX #2

target_link_libraries(imgui PUBLIC
    glfw
    glad::glad
)

# -------------------------
# Fabsim Core Library
# -------------------------
file(GLOB FABSIM_CORE_SRC
    src/*.cpp
)

# REMOVE main.cpp FROM CORE  (FIX #3)
list(REMOVE_ITEM FABSIM_CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

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

target_include_directories(fabsim_app PRIVATE
    3rdparty/imgui
    3rdparty/imgui/backends
)

target_link_libraries(fabsim_app PRIVATE
    fabsim_core
    imgui
    glfw
    glad::glad
    opengl32
)

