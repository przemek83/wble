#include "FilterDatesTest.h"

#include <QCheckBox>
#include <QDateEdit>
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
    FilterDates filter(" ", fromDate_, toDate_, true);
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

void FilterDatesTest::testToggling()
{
    FilterDates filter(" ", fromDate_, toDate_, true);
    auto lineEdits = filter.findChildren<QDateEdit*>();
    auto checkBoxes = filter.findChildren<QCheckBox*>();
    for (const auto widget : lineEdits)
        QCOMPARE(widget->isEnabled(), true);
    for (const auto widget : checkBoxes)
        QCOMPARE(widget->isEnabled(), true);

    filter.setChecked(false);
    QApplication::processEvents();
    for (const auto widget : lineEdits)
        QCOMPARE(widget->isEnabled(), false);
    for (const auto widget : checkBoxes)
        QCOMPARE(widget->isEnabled(), false);
}
