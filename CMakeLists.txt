cmake_minimum_required(VERSION 3.15)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI application" ON)

include(FetchContent)

# ---------------------- Dependencies ----------------------

# Eigen (header-only)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# tinyobjloader (header-only)
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v2.0.0
)
FetchContent_MakeAvailable(tinyobjloader)

# GLAD (only needed for GUI)
if(BUILD_GUI)
  FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
  )
  FetchContent_MakeAvailable(glad)

  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
  )
  FetchContent_MakeAvailable(glfw)

  find_package(OpenGL REQUIRED)
endif()

# ---------------------- Core Library ----------------------

file(GLOB FABCORE_SOURCES src/*.cpp)
add_library(fabcore ${FABCORE_SOURCES})
target_include_directories(fabcore PUBLIC src ${eigen_SOURCE_DIR})
target_link_libraries(fabcore PUBLIC tinyobjloader)

# ---------------------- CLI App ----------------------

add_executable(fabsim src/cli/main.cpp)
target_link_libraries(fabsim PRIVATE fabcore)

# ---------------------- GUI App ----------------------

if(BUILD_GUI)
  add_executable(fabsim_gui src/gui/main.cpp)

  target_link_libraries(fabsim_gui
    PRIVATE fabcore
    glfw
    glad
    OpenGL::GL
  )

  if(APPLE)
    target_link_libraries(fabsim_gui PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
  endif()
endif()
