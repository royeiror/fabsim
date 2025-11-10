
#pragma once
#include <vector>
#include <Eigen/Core>

class Viewer {
public:
    Viewer();
    void run();
private:
    void init();
    void render();
    unsigned int vao = 0, vbo = 0;
    std::vector<Eigen::Vector3f> points;
};
