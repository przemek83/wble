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

std::pair<int, int> getStartingAnglesInfinite(int progressCounter)
{
    const int firstAngle{static_cast<int>(
        std::lround(progressCounter * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE))};
    const int secondAngle{static_cast<int>(std::lround(
        (HALF_CIRCLE_ANGLE + (progressCounter * HUNDREDTH_OF_FULL_CIRCLE)) *
        FULL_DEGREE))};
    return {firstAngle, secondAngle};
}

int getStartingAngleCounter()
{
    constexpr int startAngle{QUARTER_CIRCLE_ANGLE * FULL_DEGREE};
    return startAngle;
}

int getSpanAngleInfinite()
{
    constexpr int step{45};
    constexpr const int spanAngle{-step * FULL_DEGREE};
    return spanAngle;
}

int getSpanAngleCounter(int progressCounter)
{
    const int spanAngle{static_cast<int>(std::lround(
        -progressCounter * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE))};
    return spanAngle;
}
}  // namespace utilities
