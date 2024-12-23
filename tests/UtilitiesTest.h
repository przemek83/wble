#pragma once

#include <QObject>

class UtilitiesTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testAnglesInfiniteZeroProgress();

    static void testAnglesInfiniteHalfProgress();

    static void testAnglesInfiniteFullProgress();

    static void testGetSpanAngleInfinite();

    static void testStartingAngleCounter();

    static void testGetSpanAngleCounterZero();
    static void testGetSpanAngleCounterHalf();
    static void testGetSpanAngleCounterFull();
};
