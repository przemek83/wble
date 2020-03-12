#ifndef FILTERDATESTEST_H
#define FILTERDATESTEST_H

#include <QDate>
#include <QObject>

class FilterDatesTest: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();

    void testFilterEmptyDatesToggle();

    void testToggling();

    void testProperInitOfEmptyDatesCheckbox();

    void testChangingDates();

private:
    QDate fromDate_;
    QDate toDate_;

    static constexpr int NO_SIGNAL {0};
    static constexpr int SIGNAL_RECEIVED {1};
};

#endif // FILTERDATESTEST_H
