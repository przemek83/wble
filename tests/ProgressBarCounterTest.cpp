#include "ProgressBarCounterTest.h"

#include <QTest>

#include "ProgressBarCommon.h"
#include "ProgressBarCounter.h"

void ProgressBarCounterTest::testStarting()
{
    ProgressBarCounter progressBar("", max_);
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarCounterTest::testFirstUpdatingProgress()
{
    ProgressBarCounter progressBar("", max_);
    progressBar.updateProgress(max_ / 2);
    QCOMPARE(progressBar.isRunning(), true);
}

void ProgressBarCounterTest::testStopping()
{
    ProgressBarCounter progressBar("", max_);
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarCounterTest::testRestarting()
{
    ProgressBarCounter progressBar("", max_);
    ProgressBarCommon::checkRestarting(progressBar);
}
