#include "Viewer.h"
#include <tiny_obj_loader.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

void RunViewer(const std::string& objPath) {
    if (!glfwInit()) return;

    GLFWwindow* window = glfwCreateWindow(800, 600, "fabsim Viewer", nullptr, nullptr);
    if (!window) return;
    glfwMakeContextCurrent(window);

    glewInit();

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(objPath)) {
        std::cerr << "Failed loading OBJ: " << objPath << "\n";
        return;
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();

    std::vector<float> vertices;
    for (const auto& shape : shapes) {
        for (const auto& idx : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
        }
    }

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
