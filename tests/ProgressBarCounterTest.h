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

private:
    static constexpr int max_{100};
};
