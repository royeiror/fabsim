cmake_minimum_required(VERSION 3.20)

project(MyApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI application" ON)

include(FetchContent)

# --- Fetch Eigen without tests ---
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests" FORCE)

FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

add_subdirectory(src)

if(BUILD_GUI)
    add_subdirectory(gui)
endif()
