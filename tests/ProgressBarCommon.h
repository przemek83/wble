#ifndef PROGRESSBARCOMMON_H
#define PROGRESSBARCOMMON_H

class ProgressBar;

namespace ProgressBarCommon
{
void checkStarting(ProgressBar& progressBar);

void checkStopping(ProgressBar& progressBar);

void checkRestarting(ProgressBar& progressBar);
};

#endif // PROGRESSBARCOMMON_H
