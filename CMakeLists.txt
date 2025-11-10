cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Eigen (header-only)
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

# GUI option
option(BUILD_GUI "Build GUI application" OFF)

if(BUILD_GUI)
    include(FetchContent)

    # --- GLFW ---
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)

    # --- ImGui ---
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.90.4
    )
    FetchContent_MakeAvailable(imgui)

    # Build ImGui backend binding for GLFW + OpenGL3
    set(IMGUI_BACKEND_SOURCES
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    add_library(imgui_backend ${IMGUI_BACKEND_SOURCES})
    target_include_directories(imgui_backend PRIVATE ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
    target_link_libraries(imgui_backend PRIVATE imgui glfw)

    # OpenGL
    find_package(OpenGL REQUIRED)

    # GUI executable
    add_executable(fabsim_gui
        gui/main.cpp
        gui/viewer.cpp
        gui/viewer.h
    )

    target_include_directories(fabsim_gui PRIVATE ${imgui_SOURCE_DIR})
    target_link_libraries(fabsim_gui
        fabsim_lib
        imgui
        imgui_backend
        glfw
        OpenGL::GL
    )
endif()
