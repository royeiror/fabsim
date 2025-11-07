cmake_minimum_required(VERSION 3.20)

project(MyApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI application" ON)

include(FetchContent)

# Fetch Eigen automatically
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# If you have src/ folder for core logic:
add_subdirectory(src)

if(BUILD_GUI)
    # GUI code assumed to be in gui/ folder
    add_subdirectory(gui)
endif()
