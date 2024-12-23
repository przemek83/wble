#include "ProgressBarInfiniteTest.h"

#include <QTest>

#include <wble/ProgressBarInfinite.h>
#include "ProgressBarCommon.h"

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

void ProgressBarInfiniteTest::checkInitialPaintNoTitle()
{
    ProgressBarInfinite progressBar(QLatin1String(""));
    auto actual{progressBar.grab().toImage()};
    QImage expected(":/res/infinityInitial.png");
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}

void ProgressBarInfiniteTest::checkPaintAfterUpdateNoTitle()
{
    ProgressBarInfinite progressBar(QLatin1String(""));
    QTimerEvent event{0};
    for (int i{0}; i < 10; ++i)
        QApplication::sendEvent(&progressBar, &event);

    auto actual{progressBar.grab().toImage()};
    QImage expected(":/res/infinityUpdated.png");
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
