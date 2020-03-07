#include <QtTest/QtTest>

#include "DoubleSliderTest.h"
#include "FilterDatesTest.h"
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

    return 0;
}
