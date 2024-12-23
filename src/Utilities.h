#pragma once

#include <utility>

namespace utilities
{
bool doublesAreEqual(double left, double right);

std::pair<int, int> getStartingAnglesInfinite(int progressCounter);

int getStartingAngleCounter();

int getSpanAngleInfinite();

int getSpanAngleCounter(int progressCounter);

}  // namespace utilities
