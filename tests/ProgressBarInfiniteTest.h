#ifndef PROGRESSBARINFINITETEST_H
#define PROGRESSBARINFINITETEST_H

#include <QObject>

class ProgressBarInfiniteTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testStarting();

    void testStopping();

    void testReseting();
};

#endif // PROGRESSBARINFINITETEST_H
