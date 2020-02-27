#include <QtTest/QtTest>

#include "DoubleSliderTest.h"
#include "FilterDatesTest.h"
#include "FilterNamesTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DoubleSliderTest doubleSliderTest;
    QTest::qExec(&doubleSliderTest);

    FilterDatesTest filterDatesTest;
    QTest::qExec(&filterDatesTest);

    FilterNamesTest filterNamesTest;
    QTest::qExec(&filterNamesTest);

    return 0;
}
