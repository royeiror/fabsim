cmake_minimum_required(VERSION 3.16)
project(fabsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Eigen (header-only)
include_directories(${PROJECT_SOURCE_DIR}/deps/eigen)

# fsim core headers
include_directories(${PROJECT_SOURCE_DIR})

file(GLOB FSIM_HEADERS fsim/*.h)
file(GLOB FSIM_SOURCES fsim/*.cpp)

add_library(fabsim_lib ${FSIM_SOURCES} ${FSIM_HEADERS})
target_include_directories(fabsim_lib PUBLIC ${PROJECT_SOURCE_DIR})
