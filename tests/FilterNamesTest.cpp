#include "FilterNamesTest.h"

#include <QCheckBox>
#include <QListWidget>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "FilterNames.h"

void FilterNamesTest::initTestCase()
{
    testEntriesList_ = QStringList{"a", "b", "c", "d"};
}

void FilterNamesTest::testToggling()
{
    FilterNames filter(" ", testEntriesList_);
    auto listWidget = filter.findChild<QListWidget*>();
    auto selectAll = filter.findChild<QCheckBox*>();
    QCOMPARE(listWidget->isEnabled(), true);
    QCOMPARE(selectAll->isEnabled(), true);

    filter.setChecked(false);
    QCOMPARE(listWidget->isEnabled(), false);
    QCOMPARE(selectAll->isEnabled(), false);
}

void FilterNamesTest::testSelectAllToggling()
{
    FilterNames filter(" ", testEntriesList_);
    QSignalSpy spy(&filter, &FilterNames::newStringFilter);

    auto selectAll = filter.findChild<QCheckBox*>();
    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(testEntriesList_)});

    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{})});
}
