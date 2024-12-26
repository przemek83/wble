#include "ProgressBarInfiniteTest.h"

#include <QTest>

#include <wble/ProgressBarInfinite.h>
#include "ProgressBarCommon.h"

void ProgressBarInfiniteTest::testStarting()
{
    ProgressBarInfinite progressBar(QString::fromLatin1(""));
    ProgressBarCommon::checkStarting(progressBar);
}

void ProgressBarInfiniteTest::testStopping()
{
    ProgressBarInfinite progressBar(QString::fromLatin1(""));
    ProgressBarCommon::checkStopping(progressBar);
}

void ProgressBarInfiniteTest::testReseting()
{
    ProgressBarInfinite progressBar(QString::fromLatin1(""));
    ProgressBarCommon::checkReseting(progressBar);
}

void ProgressBarInfiniteTest::checkInitialPaintNoTitle()
{
    ProgressBarInfinite progressBar(QString::fromLatin1(""));
    auto actual{progressBar.grab().toImage()};
    QImage expected(QString::fromLatin1(":/res/infinityInitial.png"));
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}

void ProgressBarInfiniteTest::checkPaintAfterUpdateNoTitle()
{
    ProgressBarInfinite progressBar(QString::fromLatin1(""));
    QTimerEvent event{0};
    for (int i{0}; i < 10; ++i)
        QApplication::sendEvent(&progressBar, &event);

    auto actual{progressBar.grab().toImage()};
    QImage expected(QString::fromLatin1(":/res/infinityUpdated.png"));
    expected = expected.convertToFormat(actual.format());
    QCOMPARE(actual, expected);
}
