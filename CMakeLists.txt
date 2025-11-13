cmake_minimum_required(VERSION 3.16)
project(fabsim_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ---------------------- EIGEN ----------------------
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

# ---------------------- GLFW ----------------------
# Disable examples/tests/docs to avoid building all those .exe files
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# ---------------------- INCLUDE PATHS ----------------------
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${eigen_SOURCE_DIR}
)

# ---------------------- SOURCE FILES ----------------------
file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

# ---------------------- EXECUTABLE ----------------------
add_executable(fabsim_app ${FABSIM_SOURCES})
target_link_libraries(fabsim_app PRIVATE glfw)

target_include_directories(fabsim_app PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/app
  ${eigen_SOURCE_DIR}
)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

message(STATUS "Configured fabsim_app for Windows build")
