#include "ProgressBarInfiniteTest.h"

#include <QTest>

#include "ProgressBarCommon.h"
#include "ProgressBarInfinite.h"

void ProgressBarInfiniteTest::testStarting()
{
    ProgressBarInfinite progressBar(QLatin1String(""));
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarInfiniteTest::testStopping()
{
    ProgressBarInfinite progressBar(QLatin1String(""));
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarInfiniteTest::testReseting()
{
    ProgressBarInfinite progressBar(QLatin1String(""));
    ProgressBarCommon::checkReseting(progressBar);
}
