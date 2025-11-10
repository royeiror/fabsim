cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build graphical interface" ON)

include(FetchContent)

# --- Eigen ---
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# --- tinyobjloader ---
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG v1.0.6
)
FetchContent_MakeAvailable(tinyobjloader)

# --- Source files (.cpp in src/) ---
file(GLOB_RECURSE FABSIM_SOURCES CONFIGURE_DEPENDS src/*.cpp)
if(NOT FABSIM_SOURCES)
    message(FATAL_ERROR "No .cpp files found in src/. Add source files to src/")
endif()

# --- Main Library ---
add_library(fabsim_lib ${FABSIM_SOURCES})
target_include_directories(fabsim_lib PUBLIC include)
target_link_libraries(fabsim_lib PUBLIC Eigen3::Eigen tinyobjloader)

# --- GUI Build ---
if (BUILD_GUI)

    # GLAD (BUILD GLAD AS LIBRARY)
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
    )
    FetchContent_MakeAvailable(glad)
    add_library(glad_lib ${glad_SOURCE_DIR}/src/glad.c)
    target_include_directories(glad_lib PUBLIC ${glad_SOURCE_DIR}/include)

    # GLFW
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)

    # GUI Executable
    add_executable(fabsim_gui app/main.cpp)
    target_include_directories(fabsim_gui PUBLIC include ${glad_SOURCE_DIR}/include)

    target_link_libraries(fabsim_gui PRIVATE
        fabsim_lib
        glad_lib
        glfw
    )

    if(MSVC)
        target_compile_definitions(fabsim_gui PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()

endif()

message(STATUS "BUILD_GUI = ${BUILD_GUI}")
