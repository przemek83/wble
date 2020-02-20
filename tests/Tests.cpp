#include <QtTest/QtTest>

#include "DoubleSliderTest.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DoubleSliderTest constantsTest;
    QTest::qExec(&constantsTest);

    return 0;
}
