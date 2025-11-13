#include "fsim/math.hpp"
#include <cmath>

namespace fsim {

// Clamp value between [minVal, maxVal]
double clamp(double x, double minVal, double maxVal) {
    return std::max(minVal, std::min(x, maxVal));
}

// Linear interpolation
double lerp(double a, double b, double t) {
    return a + t * (b - a);
}

// Smoothstep interpolation (Hermite curve)
double smoothstep(double edge0, double edge1, double x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return x * x * (3 - 2 * x);
}

// Normalize angle to range [-π, π)
double normalizeAngle(double angle) {
    constexpr double PI = 3.14159265358979323846;
    constexpr double TWO_PI = 2.0 * PI;
    angle = std::fmod(angle + PI, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle - PI;
}

// Degrees to radians
double deg2rad(double deg) {
    constexpr double PI = 3.14159265358979323846;
    return deg * (PI / 180.0);
}

// Radians to degrees
double rad2deg(double rad) {
    constexpr double PI = 3.14159265358979323846;
    return rad * (180.0 / PI);
}

} // namespace fsim
