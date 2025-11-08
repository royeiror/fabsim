cmake_minimum_required(VERSION 3.19)

# GUI sources
file(GLOB GUI_SRC
    *.cpp
)

# ---- Fetch ImGui ----
include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.8
)
FetchContent_MakeAvailable(imgui)

# Add backend bindings for OpenGL + GLFW
set(IMGUI_BACKENDS
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui_backend ${IMGUI_BACKENDS})
target_include_directories(imgui_backend PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_backend PUBLIC glfw glad)

# ---- GUI EXECUTABLE ----
add_executable(fabsim_gui ${GUI_SRC})

target_include_directories(fabsim_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(fabsim_gui PRIVATE
    fabsim
    imgui
    imgui_backend
    glfw
    glad
    Eigen3::Eigen
)

# Windows working dir
if(WIN32)
    set_target_properties(fabsim_gui PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    )
endif()
