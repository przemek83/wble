#include "Utilities.h"

#include <algorithm>
#include <cmath>

namespace
{
constexpr int FULL_DEGREE{16};
constexpr double HUNDREDTH_OF_FULL_CIRCLE{3.6};
constexpr int QUARTER_CIRCLE_ANGLE{90};
constexpr int HALF_CIRCLE_ANGLE{2 * QUARTER_CIRCLE_ANGLE};
}  // namespace

namespace utilities
{
bool doublesAreEqual(double left, double right)
{
    static constexpr double qtDoublePrecision{1e-12};
    return std::abs(left - right) <=
           (qtDoublePrecision *
            std::max({1.0, std::abs(left), std::abs(right)}));
}

std::pair<int, int> getStartingAngles(int progressCounter)
{
    int firstAngle{static_cast<int>(
        std::lround(progressCounter * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE))};
    int secondAngle{static_cast<int>(std::lround(
        (HALF_CIRCLE_ANGLE + (progressCounter * HUNDREDTH_OF_FULL_CIRCLE)) *
        FULL_DEGREE))};
    return {firstAngle, secondAngle};
}

int getSpanAngle()
{
    constexpr int step{45};
    constexpr const int spanAngle{-step * FULL_DEGREE};
    return spanAngle;
}
}  // namespace utilities
