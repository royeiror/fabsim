cmake_minimum_required(VERSION 3.16)
project(fabsim)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# ---- Dependencies ----

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_INSTALL OFF CACHE BOOL " " FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# ---- IMGUI (local vendor) ----
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/3rdparty/imgui)
file(GLOB IMGUI_SRC
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw glad)

# ---- Core Library ----
file(GLOB FABSIM_CORE
    src/*.cpp
    include/fsim/*.h
)

add_library(fabsim_core STATIC ${FABSIM_CORE})
target_include_directories(fabsim_core PUBLIC include)
target_link_libraries(fabsim_core PUBLIC)

# ---- CLI Tool ----
add_executable(fab src/main.cpp)
target_link_libraries(fab PUBLIC fabsim_core)

# ---- GUI ----
add_executable(fabgui
    gui/gui.cpp
    gui/main.cpp
    gui/viewer.cpp
)

target_include_directories(fabgui PUBLIC include gui ${IMGUI_DIR})
target_link_libraries(fabgui PUBLIC fabsim_core imgui glfw glad)
