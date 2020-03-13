#ifndef PROGRESSBARCOUNTERTEST_H
#define PROGRESSBARCOUNTERTEST_H

#include <QObject>

class ProgressBarCounterTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testStarting();

    void testFirstUpdatingProgress();

    void testStopping();

    void testReseting();

private:
    static constexpr int max_ {100};
};

#endif // PROGRESSBARCOUNTERTEST_H
