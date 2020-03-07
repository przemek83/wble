#include <QtTest/QtTest>

#include "DoubleSliderTest.h"
#include "FilterDatesTest.h"
#include "FilterDoublesTest.h"
#include "FilterIntegersTest.h"
#include "FilterStringsTest.h"

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

    return 0;
}
