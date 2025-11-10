cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build GUI viewer" ON)

# Dependencies
include(FetchContent)

# ---------------- Eigen (header only) ----------------
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# ---------------- tinyobjloader ----------------
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# ---------------- GLFW ----------------
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# ---------------- GLAD ----------------
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
set(GLAD_PROFILE core)
set(GLAD_API gl=4.1)
FetchContent_MakeAvailable(glad)

# ---------------- ImGui ----------------
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90
)
FetchContent_MakeAvailable(imgui)

# ---------------- FSim library ----------------
file(GLOB FSIM_SRC CONFIGURE_DEPENDS
    fsim/src/*.cpp
    fsim/src/*/*.cpp
)

add_library(fabsim_lib ${FSIM_SRC})
target_include_directories(fabsim_lib PUBLIC fsim/include)
target_link_libraries(fabsim_lib PUBLIC Eigen3::Eigen tinyobjloader)

# ---------------- GUI ----------------
if(BUILD_GUI)
    file(GLOB GUI_SRC CONFIGURE_DEPENDS
        gui/*.cpp
        gui/*/*.cpp
    )

    add_executable(fabsim_gui ${GUI_SRC})

    target_include_directories(fabsim_gui PUBLIC gui fsim/include)

    target_link_libraries(fabsim_gui
        PRIVATE
            fabsim_lib
            glfw
            glad
            imgui
            opengl32
    )
endif()

# ---------------- Example CLI (optional) ----------------
file(GLOB EXAMPLES CONFIGURE_DEPENDS examples/*.cpp)
foreach(src ${EXAMPLES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} PRIVATE fabsim_lib)
endforeach()
