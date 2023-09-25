#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

int main() {
    double degrees = 31.78; // Góc trong độ
    double radians = degrees * M_PI / 180.0; // Chuyển đổi góc sang radian
    double cosValue = std::cos(radians);

    std::cout << "cos(31.78) = " << cosValue << std::endl;

    return 0;
}
