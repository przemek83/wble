#include <QTest>

#include "DoubleSliderTest.h"
#include "FilterDatesTest.h"
#include "FilterDoublesTest.h"
#include "FilterIntegersTest.h"
#include "FilterStringsTest.h"
#include "ProgressBarCounterTest.h"
#include "ProgressBarInfiniteTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DoubleSliderTest doubleSliderTest;
    QTest::qExec(&doubleSliderTest);

    FilterDatesTest filterDatesTest;
    QTest::qExec(&filterDatesTest);

    FilterStringsTest filterStringsTest;
    QTest::qExec(&filterStringsTest);

    FilterIntegersTest filterIntegersTest;
    QTest::qExec(&filterIntegersTest);

    FilterDoublesTest filterDoublesTest;
    QTest::qExec(&filterDoublesTest);

    ProgressBarCounterTest progressBarCounterTest;
    QTest::qExec(&progressBarCounterTest);

    ProgressBarInfiniteTest progressBarInfiniteTest;
    QTest::qExec(&progressBarInfiniteTest);

    return 0;
}
