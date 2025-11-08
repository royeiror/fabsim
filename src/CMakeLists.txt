file(GLOB FABSIM_CORE_SOURCES
    *.cpp
)

# Remove main.cpp from the core library
list(FILTER FABSIM_CORE_SOURCES EXCLUDE REGEX "main.cpp")

add_library(fabsim STATIC ${FABSIM_CORE_SOURCES})
target_include_directories(fabsim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(fabsim PUBLIC Eigen3::Eigen)
