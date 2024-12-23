#pragma once

#include <QObject>

class UtilitiesTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testAnglesZeroProgress();

    static void testAnglesHalfProgress();

    static void testAnglesFullProgress();

    static void testGetSpanAngle();
};
