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

// void ProgressBarCounterTest::checkInitialPaint()
// {
//     ProgressBarCounter progressBar(QLatin1String("Initial"), max_);
//     auto actual{progressBar.grab().toImage()};
//     QImage expected(":/res/counterInitial.png");
//     expected = expected.convertToFormat(actual.format());
//     QCOMPARE(actual, expected);
// }

// void ProgressBarCounterTest::checkPaintAfterUpdate()
// {
//     ProgressBarCounter progressBar(QLatin1String("Updated"), max_);
//     progressBar.updateProgress(10);
//     auto actual{progressBar.grab().toImage()};
//     QImage expected(":/res/counterUpdated.png");
//     expected = expected.convertToFormat(actual.format());
//     QCOMPARE(actual, expected);
// }

// void ProgressBarCounterTest::checkPaintFinished()
// {
//     ProgressBarCounter progressBar(QLatin1String("Finished"), max_);
//     progressBar.updateProgress(100);
//     auto actual{progressBar.grab().toImage()};
//     QImage expected(":/res/counterFinished.png");
//     expected = expected.convertToFormat(actual.format());
//     QCOMPARE(actual, expected);
// }
