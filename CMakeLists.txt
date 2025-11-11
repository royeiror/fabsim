cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent is used to automatically download dependencies
include(FetchContent)

# ---------------------- EIGEN ----------------------
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# ---------------------- GLFW ----------------------
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# ---------------------- GLAD ----------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# glad cmake default doesn't create a target, so we define one
add_library(glad STATIC
  ${glad_SOURCE_DIR}/src/glad.c
)
target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)

# ---------------------- IMGUI ----------------------
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.3
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw glad)

# ---------------------- Application ----------------------
file(GLOB FABSIM_SRC src/*.cpp)

add_executable(fabsim_app ${FABSIM_SRC})

target_include_directories(fabsim_app PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${eigen_SOURCE_DIR}
)

target_link_libraries(fabsim_app
  PRIVATE
    glfw
    glad
    imgui
)

# Windows: ensure proper subsystem
if (WIN32)
  target_compile_definitions(fabsim_app PRIVATE "_CRT_SECURE_NO_WARNINGS")
endif()
