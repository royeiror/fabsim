#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <tinyfiledialogs.h>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Vertex {
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
};

static std::vector<Vertex> g_vertices;
static std::string g_loadedFile;
static GLuint g_vao = 0, g_vbo = 0;

static void loadOBJ(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::vector<Eigen::Vector3f> positions, normals;
    std::vector<unsigned int> posIdx, normIdx;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;
        if (prefix == "v") {
            Eigen::Vector3f v;
            ss >> v.x() >> v.y() >> v.z();
            positions.push_back(v);
        } else if (prefix == "vn") {
            Eigen::Vector3f n;
            ss >> n.x() >> n.y() >> n.z();
            normals.push_back(n);
        } else if (prefix == "f") {
            std::string f1, f2, f3;
            ss >> f1 >> f2 >> f3;
            for (auto& f : {f1, f2, f3}) {
                unsigned int vi = 0, ni = 0;
                sscanf(f.c_str(), "%u//%u", &vi, &ni);
                posIdx.push_back(vi - 1);
                normIdx.push_back(ni - 1);
            }
        }
    }

    g_vertices.clear();
    for (size_t i = 0; i < posIdx.size(); ++i) {
        Vertex v;
        v.position = positions[posIdx[i]];
        v.normal = normals.size() ? normals[normIdx[i]] : Eigen::Vector3f(0, 0, 1);
        g_vertices.push_back(v);
    }

    std::cout << "Loaded OBJ with " << g_vertices.size() << " vertices\n";

    // Upload to GPU
    if (g_vbo) glDeleteBuffers(1, &g_vbo);
    if (g_vao) glDeleteVertexArrays(1, &g_vao);
    glGenVertexArrays(1, &g_vao);
    glGenBuffers(1, &g_vbo);
    glBindVertexArray(g_vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(Vertex), g_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    g_loadedFile = path;
}

static void renderMesh() {
    if (!g_vao || g_vertices.empty()) return;
    glBindVertexArray(g_vao);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)g_vertices.size());
    glBindVertexArray(0);
}

static void drawMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open...")) {
                const char* patterns[] = {"*.obj"};
                const char* path = tinyfd_openFileDialog("Open 3D File", "", 1, patterns, "OBJ files", 0);
                if (path) loadOBJ(path);
            }
            if (ImGui::MenuItem("Exit")) exit(0);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Status");
    if (!g_loadedFile.empty())
        ImGui::Text("Loaded: %s", g_loadedFile.c_str());
    else
        ImGui::Text("No file loaded.");
    ImGui::End();
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "fabsim viewer", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawMenu();

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.12f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderMesh();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
