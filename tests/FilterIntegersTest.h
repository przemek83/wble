#ifndef FILTERINTEGERSTEST_H
#define FILTERINTEGERSTEST_H

#include <QObject>

class FilterIntegersTest: public QObject
{
    Q_OBJECT
private slots:
    void testToggling();

private:
    static constexpr int NO_SIGNAL {0};
    static constexpr int SIGNAL_RECEIVED {1};
};

#endif // FILTERINTEGERSTEST_H
