cmake_minimum_required(VERSION 3.19)

file(GLOB VIEWER_SRC *.cpp)

add_executable(fabsim_viewer ${VIEWER_SRC})
target_include_directories(fabsim_viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(fabsim_viewer PRIVATE fabsim glfw glad Eigen3::Eigen tinyobjloader)
