cmake_minimum_required(VERSION 3.19)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI application" ON)
option(BUILD_VIEWER "Build Viewer application" ON)

include(FetchContent)

# -------- Fetch Eigen --------
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# -------- Fetch tinyobjloader --------
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v2.0.0rc13
)
FetchContent_MakeAvailable(tinyobjloader)

add_subdirectory(src)

if(BUILD_GUI)
    add_subdirectory(gui)
endif()

if(BUILD_VIEWER)
    add_subdirectory(viewer)
endif()

message(STATUS "Build configuration complete.")
