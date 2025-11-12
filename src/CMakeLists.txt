file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/*.cpp"
)

add_executable(fabsim_app ${SRC_FILES})

target_link_libraries(fabsim_app
    PRIVATE
        glad
        glfw
        imgui
        opengl32
)
