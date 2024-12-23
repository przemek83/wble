#include "UtilitiesTest.h"

#include <QTest>

#include "Utilities.h"

namespace
{
constexpr int FULL_CIRCLE_ANGLE{5760};
}  // namespace

void UtilitiesTest::testAnglesInfiniteZeroProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAnglesInfinite(0)};
    QCOMPARE(firstAngle, 0);
    QCOMPARE(secondAngle, FULL_CIRCLE_ANGLE / 2);
}

void UtilitiesTest::testAnglesInfiniteHalfProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAnglesInfinite(50)};
    QCOMPARE(firstAngle, FULL_CIRCLE_ANGLE / 2);
    QCOMPARE(secondAngle, FULL_CIRCLE_ANGLE);
}

void UtilitiesTest::testAnglesInfiniteFullProgress()
{
    auto [firstAngle, secondAngle]{utilities::getStartingAnglesInfinite(100)};
    QCOMPARE(firstAngle, FULL_CIRCLE_ANGLE);
    QCOMPARE(secondAngle, FULL_CIRCLE_ANGLE + FULL_CIRCLE_ANGLE / 2);
}

void UtilitiesTest::testGetSpanAngleInfinite()
{
    const int spanAngle{utilities::getSpanAngleInfinite()};
    QCOMPARE(spanAngle, -720);
}

void UtilitiesTest::testStartingAngleCounter()
{
    const int angle{utilities::getStartingAngleCounter()};
    QCOMPARE(angle, 1440);
}

void UtilitiesTest::testGetSpanAngleCounterZero()
{
    const int spanAngle{utilities::getSpanAngleCounter(0)};
    QCOMPARE(spanAngle, 0);
}

void UtilitiesTest::testGetSpanAngleCounterHalf()
{
    const int spanAngle{utilities::getSpanAngleCounter(50)};
    QCOMPARE(spanAngle, -FULL_CIRCLE_ANGLE / 2);
}

void UtilitiesTest::testGetSpanAngleCounterFull()
{
    const int spanAngle{utilities::getSpanAngleCounter(100)};
    QCOMPARE(spanAngle, -FULL_CIRCLE_ANGLE);
}
