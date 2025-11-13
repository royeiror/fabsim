cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# ---------------------- GLAD ----------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

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
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw glad)

# ---------------------- tinyfiledialogs ----------------------
add_library(tinyfiledialogs src/app/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs PUBLIC
  ${CMAKE_SOURCE_DIR}/src/app
)

# ---------------------- SOURCE FILES ----------------------
file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

# Exclude src/main.cpp
list(FILTER FABSIM_SOURCES EXCLUDE REGEX ".*/src/main.cpp$")

# Exclude old math.cpp duplicates
list(FILTER FABSIM_SOURCES EXCLUDE REGEX ".*/src/math.cpp$")

# ---------------------- EXECUTABLE ----------------------
add_executable(fabsim_app ${FABSIM_SOURCES})

target_include_directories(fabsim_app PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/app
  ${eigen_SOURCE_DIR}
  ${glad_SOURCE_DIR}/include
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(fabsim_app PRIVATE
  glfw
  glad
  imgui
  tinyfiledialogs
)

if (WIN32)
  target_compile_definitions(fabsim_app PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX)
  target_link_libraries(fabsim_app PRIVATE opengl32)
endif()

message(STATUS "Building fabsim for Windows with GLFW + GLAD + ImGui + Eigen + tinyfiledialogs")
