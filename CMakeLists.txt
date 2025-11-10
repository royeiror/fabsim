cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Eigen (header-only)
include_directories(${PROJECT_SOURCE_DIR}/deps/eigen)

# fsim core
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect only .cpp files in fsim/
file(GLOB FSIM_SOURCES
    ${PROJECT_SOURCE_DIR}/fsim/*.cpp
)

if(NOT FSIM_SOURCES)
    message(FATAL_ERROR "No source files found in fsim/. You are not in the correct repo root.")
endif()

add_library(fabsim_lib ${FSIM_SOURCES})
target_include_directories(fabsim_lib PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/eigen
)

# Optional GUI toggle
option(BUILD_GUI "Build the GUI viewer" OFF)

if(BUILD_GUI)
    # Fetch glfw + imgui automatically
    include(FetchContent)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)

    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.0
    )
    FetchContent_MakeAvailable(imgui)

    file(GLOB GUI_SOURCES
        ${PROJECT_SOURCE_DIR}/gui/*.cpp
    )

    if(NOT GUI_SOURCES)
        message(FATAL_ERROR "BUILD_GUI=ON but gui/ is empty. GUI code has not been added yet.")
    endif()

    add_executable(fabsim_gui ${GUI_SOURCES})
    target_link_libraries(fabsim_gui
        PRIVATE fabsim_lib glfw opengl32
    )
endif()
