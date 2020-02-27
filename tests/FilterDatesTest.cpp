#include "FilterDatesTest.h"

#include <QCheckBox>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "FilterDates.h"

void FilterDatesTest::initTestCase()
{
    fromDate_ = QDate(2010, 4, 14);
    toDate_ = QDate(2010, 7, 21);
}

void FilterDatesTest::testFilterEmptyDatesToggle()
{
    FilterDates filter(" ", fromDate_, toDate_, false);
    QSignalSpy spy(&filter, &FilterDates::newDateFilter);

    auto ignoreEmptyDates = filter.findChild<QCheckBox*>();
    ignoreEmptyDates->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedSignalParams {fromDate_, toDate_, true};
    QCOMPARE(spy.takeFirst(), expectedSignalParams);

    ignoreEmptyDates->toggle();
    expectedSignalParams = {fromDate_, toDate_, false};
    QCOMPARE(spy.takeFirst(), expectedSignalParams);
}
