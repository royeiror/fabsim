cmake_minimum_required(VERSION 3.15)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI application" ON)

include(FetchContent)

# ---- Eigen ----
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# ---- tinyobjloader ----
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# ---- fsim headers ----
# These exist in your repo: include/fsim/*.h
set(FSIM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- Source files ----
file(GLOB FABSIM_SOURCES
    src/*.cpp
    src/*.h
)

add_executable(fabsim ${FABSIM_SOURCES})

target_include_directories(fabsim PRIVATE
    ${FSIM_INCLUDE}
    ${eigen_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
)

# ---- GUI Option ----
if(BUILD_GUI)
    add_definitions(-DFABSIM_GUI)

    # Fetch GLFW
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)

    # Fetch ImGui
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.90.4
    )
    FetchContent_MakeAvailable(imgui)

    set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    add_library(imgui_lib ${IMGUI_SOURCES})
    target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
    )
    target_link_libraries(imgui_lib PRIVATE glfw OpenGL::GL)

    find_package(OpenGL REQUIRED)

    target_link_libraries(fabsim PRIVATE imgui_lib glfw OpenGL::GL)
endif()
