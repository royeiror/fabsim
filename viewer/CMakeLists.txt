file(GLOB VIEWER_SRC
    *.cpp
)

add_executable(fabsim_viewer ${VIEWER_SRC})
target_include_directories(fabsim_viewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(fabsim_viewer PRIVATE
    fabsim
    tinyobjloader
    glfw
    glad
    Eigen3::Eigen
)

# Ensure Windows finds runtime DLLs
if(WIN32)
    set_target_properties(fabsim_viewer PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    )
endif()
