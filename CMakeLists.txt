cmake_minimum_required(VERSION 3.10)
project(fabsim)

# Detects whether this is a top-level project
get_directory_property(FABSIM_PARENT_DIR PARENT_DIRECTORY)
if(NOT FABSIM_PARENT_DIR)
    set(FABSIM_TOPLEVEL_PROJECT ON)
else()
    set(FABSIM_TOPLEVEL_PROJECT OFF)
endif()

# Build tests
option(FABSIM_BUILD_TESTS      "Build fabsim unit test"        ${FABSIM_TOPLEVEL_PROJECT})

### conditionally compile certain modules depending on libraries found on the system
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

### Adding fabsim: choose the path to your local copy fabsim
include(fabsim)

if(FABSIM_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# Glad (OpenGL loader)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.0
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(fabsim_gui
    src/main.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(fabsim_gui PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glad_SOURCE_DIR}/include
)

target_link_libraries(fabsim_gui
    glfw
    glad
    opengl32
)
# --- Dependencies for viewer ---
include(FetchContent)

# tinyobjloader
include(FetchContent)

FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)

set(TINYOBJLOADER_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(TINYOBJLOADER_BUILD_OBJ_STANDALONE OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(tinyobjloader)


if (TARGET tinyobjloader-examples)
    set_target_properties(tinyobjloader-examples PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()
if (TARGET tinyobjloader-shared)
    set_target_properties(tinyobjloader-shared PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

# Disable building examples/tests to avoid subproject failures
if (TARGET tinyobjloader-examples)
    set_target_properties(tinyobjloader-examples PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()
if (TARGET tinyobjloader-shared)
    set_target_properties(tinyobjloader-shared PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()


# OpenGL + GLEW from vcpkg
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# Build Viewer
add_executable(fabsim_viewer
    viewer/Viewer.cpp
    viewer/Viewer.h
    viewer/shaders/simple.vert
    viewer/shaders/simple.frag
)

target_include_directories(fabsim_viewer PRIVATE viewer)

target_link_libraries(fabsim_viewer
    PRIVATE
        tinyobjloader
        OpenGL::GL
        GLEW::GLEW
)

