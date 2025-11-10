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
message(STATUS "Eigen included at: ${eigen_SOURCE_DIR}")

# ---- tinyobjloader ----
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)
message(STATUS "tinyobjloader included at: ${tinyobjloader_SOURCE_DIR}")

# ---- Source ----
file(GLOB FABSIM_SOURCES
    src/*.cpp
    src/*.h
)

add_executable(fabsim ${FABSIM_SOURCES})
target_include_directories(fabsim PRIVATE
    ${eigen_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
)

# ---- GUI Option ----
if(BUILD_GUI)
    add_definitions(-DFABSIM_GUI)
    message(STATUS "GUI build enabled")

    # If your GUI uses GLFW + OpenGL, enable these:
    find_package(OpenGL REQUIRED)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)

    target_link_libraries(fabsim PRIVATE glfw OpenGL::GL)
else()
    message(STATUS "GUI build disabled (CLI only)")
endif()
