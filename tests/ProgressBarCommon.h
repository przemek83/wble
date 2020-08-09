#pragma once

class ProgressBar;

namespace ProgressBarCommon
{
void checkStarting(ProgressBar& progressBar);

void checkStopping(ProgressBar& progressBar);

void checkReseting(ProgressBar& progressBar);
};  // namespace ProgressBarCommon
