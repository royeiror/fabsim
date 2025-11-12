cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# EIGEN (local)
# -------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/deps/eigen)

# -------------------------------------------------
# FSIM (local headers)
# -------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/fsim)

# -------------------------------------------------
# GLFW
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

# -------------------------------------------------
# GLAD
# -------------------------------------------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# -------------------------------------------------
# IMGUI
# -------------------------------------------------
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
# SOURCE FILES
# -------------------------------------------------
file(GLOB_RECURSE FABSIM_SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/core/*.cpp"
  "${CMAKE_SOURCE_DIR}/app/*.cpp"
  "${CMAKE_SOURCE_DIR}/viewer/*.cpp"
  "${CMAKE_SOURCE_DIR}/gui/*.cpp"
)

add_executable(fabsim_app ${FABSIM_SOURCES})

target_include_directories(fabsim_app PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/fsim
  ${PROJECT_SOURCE_DIR}/deps/eigen
)

target_link_libraries(fabsim_app
  PRIVATE
    glfw
    glad
    imgui
)

# -------------------------------------------------
# WINDOWS SETTINGS
# -------------------------------------------------
if (WIN32)
  target_compile_definitions(fabsim_app PRIVATE "_CRT_SECURE_NO_WARNINGS")
  set_property(TARGET fabsim_app PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()
