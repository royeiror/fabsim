#pragma once
#include <Eigen/Dense>

namespace fsim {

// Safe normalization — avoids division by zero and type mismatch
inline Eigen::Vector3d safeNormalize(const Eigen::Vector3d& v) {
    double n = v.norm();
    if (n == 0.0)
        return Eigen::Vector3d::Zero();
    return v / n;
}

double clamp(double x, double minVal, double maxVal);
double lerp(double a, double b, double t);
double smoothstep(double edge0, double edge1, double x);
double normalizeAngle(double angle);
double deg2rad(double deg);
double rad2deg(double rad);

} // namespace fsim
