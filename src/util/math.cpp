#include "math.hpp"
#include <cmath>
#include <algorithm>

namespace fsim {

double clamp(double x, double minVal, double maxVal) {
    return std::max(minVal, std::min(maxVal, x));
}

double lerp(double a, double b, double t) {
    return a + t * (b - a);
}

double smoothstep(double edge0, double edge1, double x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return x * x * (3 - 2 * x);
}

double normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2.0 * M_PI;
    while (angle < -M_PI) angle += 2.0 * M_PI;
    return angle;
}

double deg2rad(double deg) {
    return deg * (M_PI / 180.0);
}

double rad2deg(double rad) {
    return rad * (180.0 / M_PI);
}

} // namespace fsim
