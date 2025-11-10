cmake_minimum_required(VERSION 3.14)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI viewer" ON)

# --- FetchContent setup
include(FetchContent)

# Eigen (header-only)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# tinyobjloader
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v2.0.0
)
FetchContent_MakeAvailable(tinyobjloader)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# glad (OpenGL loader)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# imgui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.0
)
FetchContent_MakeAvailable(imgui)


# --- Core library
file(GLOB FSIM_SRC
  "fsim/*.cpp"
  "fsim/*.h"
)

if(NOT FSIM_SRC)
  message(FATAL_ERROR "No source files found in fsim/.")
endif()

add_library(fabsim_lib STATIC ${FSIM_SRC})
target_include_directories(fabsim_lib PUBLIC fsim ${eigen_SOURCE_DIR})
target_link_libraries(fabsim_lib PUBLIC tinyobjloader)


# --- GUI
if(BUILD_GUI)
    file(GLOB GUI_SRC
        "gui/*.cpp"
        "gui/*.h"
    )

    add_executable(fabsim_gui ${GUI_SRC})

    target_include_directories(fabsim_gui PUBLIC
        gui
        ${eigen_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
    )

    target_link_libraries(fabsim_gui
        PRIVATE
        fabsim_lib
        glfw
        glad
    )

    # imgui backend build
    target_sources(fabsim_gui PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

endif()
