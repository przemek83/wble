#ifndef PROGRESSBARINFINITETEST_H
#define PROGRESSBARINFINITETEST_H

#include <QObject>

class ProgressBarInfiniteTest : public QObject
{
    Q_OBJECT
private slots:
    void testStarting();

    void testStopping();

    void testRestarting();
};

#endif // PROGRESSBARINFINITETEST_H
