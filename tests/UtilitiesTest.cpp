#include "UtilitiesTest.h"

#include <QTest>

#include "Utilities.h"

void UtilitiesTest::testAnglesZeroProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAngles(0)};
    QCOMPARE(firstAngle, 0);
    QCOMPARE(secondAngle, 2880);
}

void UtilitiesTest::testAnglesHalfProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAngles(50)};
    QCOMPARE(firstAngle, 2880);
    QCOMPARE(secondAngle, 5760);
}

void UtilitiesTest::testAnglesFullProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAngles(100)};
    QCOMPARE(firstAngle, 5760);
    QCOMPARE(secondAngle, 8640);
}

void UtilitiesTest::testGetSpanAngle()
{
    const int spanAngle{utilities::getSpanAngle()};
    QCOMPARE(spanAngle, -720);
}
