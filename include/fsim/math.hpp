#pragma once
#include <Eigen/Dense>
#include <cmath>

namespace fsim {
namespace math {

// Safe normalization
inline Eigen::Vector3d normalize(const Eigen::Vector3d& v) {
    double n = v.norm();
    return n > 1e-12 ? v / n : Eigen::Vector3d::Zero();
}

// Cross product
inline Eigen::Vector3d cross(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
    return a.cross(b);
}

// Dot product
inline double dot(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
    return a.dot(b);
}

// Angle between two vectors
inline double angle_between(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
    double denom = a.norm() * b.norm();
    if (denom < 1e-12) return 0.0;
    double cosang = std::max(-1.0, std::min(1.0, a.dot(b) / denom));
    return std::acos(cosang);
}

// Project vector a onto b
inline Eigen::Vector3d project(const Eigen::Vector3d& a, const Eigen::Vector3d& b) {
    double denom = b.squaredNorm();
    if (denom < 1e-12) return Eigen::Vector3d::Zero();
    return (a.dot(b) / denom) * b;
}

} // namespace math
} // namespace fsim
