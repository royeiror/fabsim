cmake_minimum_required(VERSION 3.16)
project(fabsim_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Dependencies (Eigen and GLFW)
# ---------------------------------------------------------------------------

include(FetchContent)

# Fetch Eigen (header-only, nothing to build or install)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(eigen)

# Fetch GLFW (only if needed)
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
  message(STATUS "GLFW not found, fetching...")
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
  )
  FetchContent_MakeAvailable(glfw)
endif()

# ---------------------------------------------------------------------------
# Include paths
# ---------------------------------------------------------------------------

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/app
  ${eigen_SOURCE_DIR}
)

# ---------------------------------------------------------------------------
# Source files
# ---------------------------------------------------------------------------

file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------

add_executable(fabsim_app ${FABSIM_SOURCES})

target_link_libraries(fabsim_app PRIVATE glfw)

target_include_directories(fabsim_app PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/app
  ${eigen_SOURCE_DIR}
)

# ---------------------------------------------------------------------------
# Windows-specific options
# ---------------------------------------------------------------------------

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_compile_options(/wd4996)
endif()

# ---------------------------------------------------------------------------
# Summary
# ---------------------------------------------------------------------------

message(STATUS "Configured fabsim_app successfully for Windows build")
message(STATUS "Eigen source: ${eigen_SOURCE_DIR}")
