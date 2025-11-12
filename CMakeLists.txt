cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# LOCAL INCLUDES
# -------------------------------------------------
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/fsim
  ${CMAKE_SOURCE_DIR}/include/fsim/util
  ${CMAKE_SOURCE_DIR}/core
  ${CMAKE_SOURCE_DIR}/deps/eigen
)

# -------------------------------------------------
# GLFW / GLAD / IMGUI
# -------------------------------------------------
include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

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

# -------------------------------------------------
# FABSIM SOURCES
# -------------------------------------------------
file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/core/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
  "${CMAKE_SOURCE_DIR}/viewer/*.cpp"
  "${CMAKE_SOURCE_DIR}/gui/*.cpp"
)

# -------------------------------------------------
# EIGEN DOWNLOAD (if not found locally)
# -------------------------------------------------
include(FetchContent)

FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

target_include_directories(fabsim_app PUBLIC ${eigen_SOURCE_DIR})


add_executable(fabsim_app ${FABSIM_SOURCES})

target_include_directories(fabsim_app PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/fsim
  ${PROJECT_SOURCE_DIR}/deps/eigen
  ${PROJECT_SOURCE_DIR}/core
)

target_link_libraries(fabsim_app
  PRIVATE
    glfw
    glad
    imgui
)

# -------------------------------------------------
# WINDOWS FIXES
# -------------------------------------------------
if (WIN32)
  target_compile_definitions(fabsim_app PRIVATE "_CRT_SECURE_NO_WARNINGS")
  set_property(TARGET fabsim_app PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()
