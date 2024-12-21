#pragma once

#include <QObject>

class ProgressBarCounterTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testStarting();

    static void testFirstUpdatingProgress();

    static void testStopping();

    static void testReseting();

    static void checkInitialPaint();

    static void checkPaintAfterUpdate();

    static void checkPaintFinished();

private:
    static constexpr int max_{100};
};
