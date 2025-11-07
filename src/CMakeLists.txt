add_library(core STATIC core.cpp core.h)

target_link_libraries(core PUBLIC Eigen3::Eigen)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
