#pragma once

#include <QObject>

class ProgressBarInfiniteTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testStarting();

    void testStopping();

    void testReseting();
};
