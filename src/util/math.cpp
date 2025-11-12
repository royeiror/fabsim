#include <Eigen/Dense>
#include <cmath>

namespace fsim {

// Cross matrix of a 3D vector
Eigen::Matrix3d cross_matrix(const Eigen::Vector3d& v) {
    Eigen::Matrix3d m;
    m <<  0, -v.z(),  v.y(),
          v.z(),  0, -v.x(),
         -v.y(),  v.x(),  0;
    return m;
}

// Parallel transport of a vector along another
Eigen::Vector3d parallel_transport(
    const Eigen::Vector3d& u,
    const Eigen::Vector3d& t0,
    const Eigen::Vector3d& t1)
{
    double dot = std::clamp(t0.dot(t1), -1.0, 1.0);
    double angle = std::acos(dot);
    if (angle < 1e-9) return u;

    Eigen::Vector3d axis = t0.cross(t1);
    double len = axis.norm();
    if (len < 1e-9) return u;
    axis.normalize();

    Eigen::Matrix3d K = cross_matrix(axis);
    Eigen::Matrix3d R = Eigen::Matrix3d::Identity()
                      + std::sin(angle) * K
                      + (1 - std::cos(angle)) * (K * K);
    return R * u;
}

// Signed angle between two vectors around an axis
double signed_angle(
    const Eigen::Vector3d& u,
    const Eigen::Vector3d& v,
    const Eigen::Vector3d& axis)
{
    Eigen::Vector3d u_n = u.normalized();
    Eigen::Vector3d v_n = v.normalized();
    double angle = std::acos(std::clamp(u_n.dot(v_n), -1.0, 1.0));
    double sign = (axis.dot(u_n.cross(v_n)) >= 0) ? 1.0 : -1.0;
    return angle * sign;
}

// Tangent of half the angle (used in rod formulations)
double tan_angle_2(
    const Eigen::Vector3d& u,
    const Eigen::Vector3d& v,
    const Eigen::Vector3d& axis)
{
    double s = axis.dot(u.cross(v));
    double c = u.dot(v);
    return s / (1.0 + c);
}

} // namespace fsim
