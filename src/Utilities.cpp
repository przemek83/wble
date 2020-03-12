#include "Utilities.h"

namespace Utilities
{
bool doublesAreEqual(double left, double right)
{
    static constexpr double qtDoublePrecision {1e-12};
    return std::abs(left - right) <=
           qtDoublePrecision * std::max({ 1.0, std::abs(left), std::abs(right) });
}
} // namespace Utilities
