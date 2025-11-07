file(GLOB FABSIM_CORE_SOURCES
    *.cpp
)

add_library(fabsim STATIC ${FABSIM_CORE_SOURCES})
target_include_directories(fabsim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(fabsim PUBLIC Eigen3::Eigen)
