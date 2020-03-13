#include "ProgressBarCommon.h"

#include <QTest>

#include "ProgressBar.h"

namespace ProgressBarCommon
{
void checkStarting(ProgressBar& progressBar)
{
    QCOMPARE(progressBar.isRunning(), false);
    progressBar.start();
    QCOMPARE(progressBar.isRunning(), true);
}

void checkStopping(ProgressBar& progressBar)
{
    progressBar.start();
    progressBar.stop();
    QCOMPARE(progressBar.isRunning(), false);
}

void checkRestarting(ProgressBar& progressBar)
{
    progressBar.start();
    progressBar.restart();
    QCOMPARE(progressBar.isRunning(), true);
}
}  // namespace ProgressBarCommon
