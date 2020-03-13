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

void checkReseting(ProgressBar& progressBar)
{
    progressBar.start();
    progressBar.reset();
    QCOMPARE(progressBar.isRunning(), false);
}
}  // namespace ProgressBarCommon
