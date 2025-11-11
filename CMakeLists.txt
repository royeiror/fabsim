cmake_minimum_required(VERSION 3.10)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --------------------------------------------------------------------
# Fetch Eigen
# --------------------------------------------------------------------
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# --------------------------------------------------------------------
# Fetch tinyobjloader
# --------------------------------------------------------------------
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# --------------------------------------------------------------------
# Fetch glad
# --------------------------------------------------------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# --------------------------------------------------------------------
# Fetch GLFW (fixes your error)
# --------------------------------------------------------------------
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# --------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------
include_directories(
    ${eigen_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

# --------------------------------------------------------------------
# Main executable (fab)
# --------------------------------------------------------------------
file(GLOB FABSIM_SOURCES src/*.cpp)
add_executable(fab ${FABSIM_SOURCES})
target_link_libraries(fab PRIVATE tinyobjloader)

# --------------------------------------------------------------------
# GUI build (optional)
# --------------------------------------------------------------------
option(BUILD_GUI "Build OpenGL GUI viewer" ON)

if(BUILD_GUI)
    file(GLOB GUI_SOURCES gui/*.cpp)
    add_executable(fabgui ${GUI_SOURCES})
    target_link_libraries(fabgui PRIVATE glfw glad tinyobjloader)
    target_include_directories(fabgui PRIVATE gui/)
endif()
