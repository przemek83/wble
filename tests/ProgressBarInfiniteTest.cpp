#include "ProgressBarInfiniteTest.h"

#include <QTest>

#include "ProgressBarCommon.h"
#include "ProgressBarInfinite.h"

void ProgressBarInfiniteTest::testStarting()
{
    ProgressBarInfinite progressBar("");
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarInfiniteTest::testStopping()
{
    ProgressBarInfinite progressBar("");
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarInfiniteTest::testRestarting()
{
    ProgressBarInfinite progressBar("");
    ProgressBarCommon::checkRestarting(progressBar);
}
