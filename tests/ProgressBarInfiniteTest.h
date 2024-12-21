#pragma once

#include <QObject>

class ProgressBarInfiniteTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testStarting();

    static void testStopping();

    static void testReseting();

    static void checkInitialPaint();

    static void checkPaintAfterUpdate();
};
