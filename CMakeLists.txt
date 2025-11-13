cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
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
FetchContent_MakeAvailable(glfw)

# ---------------------- GLAD ----------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# ---------------------- SOURCE FILES ----------------------
file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

# ---------------------- EXECUTABLE ----------------------
add_executable(fabsim_app ${FABSIM_SOURCES})

target_include_directories(fabsim_app PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/app
  ${eigen_SOURCE_DIR}
  ${glad_SOURCE_DIR}/include
)

target_link_libraries(fabsim_app PRIVATE glfw glad)

# ---------------------- WINDOWS SETTINGS ----------------------
if (WIN32)
  target_compile_definitions(fabsim_app PRIVATE
    _CRT_SECURE_NO_WARNINGS
    NOMINMAX
  )
endif()

# ---------------------- OUTPUT INFO ----------------------
message(STATUS "Building fabsim for Windows with GLFW + GLAD + Eigen")
message(STATUS "Output binary will be in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
