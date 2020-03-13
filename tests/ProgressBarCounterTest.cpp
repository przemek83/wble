#include "ProgressBarCounterTest.h"

#include <QTest>

#include "ProgressBarCommon.h"
#include "ProgressBarCounter.h"

void ProgressBarCounterTest::testStarting()
{
    ProgressBarCounter progressBar(QLatin1String(""), max_);
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarCounterTest::testFirstUpdatingProgress()
{
    ProgressBarCounter progressBar(QLatin1String(""), max_);
    progressBar.updateProgress(max_ / 2);
    QCOMPARE(progressBar.isRunning(), true);
}

void ProgressBarCounterTest::testStopping()
{
    ProgressBarCounter progressBar(QLatin1String(""), max_);
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarCounterTest::testReseting()
{
    ProgressBarCounter progressBar(QLatin1String(""), max_);
    ProgressBarCommon::checkReseting(progressBar);
}
