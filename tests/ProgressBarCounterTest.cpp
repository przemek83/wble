#include "ProgressBarCounterTest.h"

#include <QTest>

#include "ProgressBarCounter.h"

void ProgressBarCounterTest::testStarting()
{
    ProgressBarCounter progressBar("", max_);
    QCOMPARE(progressBar.isRunning(), false);
    progressBar.start();
    QCOMPARE(progressBar.isRunning(), true);
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
    progressBar.start();
    progressBar.stop();
    QCOMPARE(progressBar.isRunning(), false);
}

void ProgressBarCounterTest::testRestarting()
{
    ProgressBarCounter progressBar("", max_);
    progressBar.start();
    progressBar.restart();
    QCOMPARE(progressBar.isRunning(), true);
}
