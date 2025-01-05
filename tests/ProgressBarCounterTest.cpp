#include "ProgressBarCounterTest.h"

#include <QTest>

#include <wble/ProgressBarCounter.h>
#include "ProgressBarCommon.h"

void ProgressBarCounterTest::testStarting()
{
    ProgressBarCounter progressBar(QString::fromLatin1(""), max_);
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarCounterTest::testFirstUpdatingProgress()
{
    ProgressBarCounter progressBar(QString::fromLatin1(""), max_);
    progressBar.updateProgress(max_ / 2);
    QCOMPARE(progressBar.isRunning(), true);
}

void ProgressBarCounterTest::testSecondUpdatingProgress()
{
    ProgressBarCounter progressBar(QString::fromLatin1(""), max_);
    progressBar.updateProgress(max_ / 4);
    progressBar.updateProgress(max_ / 2);
    QCOMPARE(progressBar.isRunning(), true);
}

void ProgressBarCounterTest::testStopping()
{
    ProgressBarCounter progressBar(QString::fromLatin1(""), max_);
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarCounterTest::testReseting()
{
    ProgressBarCounter progressBar(QString::fromLatin1(""), max_);
    ProgressBarCommon::checkReseting(progressBar);
}
