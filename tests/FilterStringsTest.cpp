#include "FilterStringsTest.h"

#include <QCheckBox>
#include <QListWidget>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "FilterStrings.h"

void FilterStringsTest::initTestCase()
{
    testEntriesList_ = QStringList{"a", "b", "c", "d"};
}

void FilterStringsTest::testToggling()
{
    FilterStrings filter(" ", testEntriesList_);
    auto listWidget = filter.findChild<QListWidget*>();
    auto selectAll = filter.findChild<QCheckBox*>();
    QCOMPARE(listWidget->isEnabled(), true);
    QCOMPARE(selectAll->isEnabled(), true);

    filter.setChecked(false);
    QCOMPARE(listWidget->isEnabled(), false);
    QCOMPARE(selectAll->isEnabled(), false);
}

void FilterStringsTest::testSelectAllToggling()
{
    FilterStrings filter(" ", testEntriesList_);
    QSignalSpy spy(&filter, &FilterStrings::newStringFilter);

    auto selectAll = filter.findChild<QCheckBox*>();
    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(testEntriesList_)});

    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{})});
}

void FilterStringsTest::testListItemChecking()
{
    FilterStrings filter(" ", testEntriesList_);
    QSignalSpy spy(&filter, &FilterStrings::newStringFilter);
    const auto listWidget = filter.findChild<QListWidget*>();
    const auto item = listWidget->item(testEntriesList_.indexOf("b"));
    const QRect itemRect = listWidget->visualItemRect(item);
    QTest::mouseClick(listWidget->viewport(), Qt::LeftButton, Qt::NoModifier, itemRect.center());

    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {"b"});
    QCOMPARE(spy.count(), NO_SIGNAL);

    QApplication::processEvents();
    QTest::mouseClick(listWidget->viewport(), Qt::LeftButton, Qt::NoModifier, itemRect.center());
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{})});
}
