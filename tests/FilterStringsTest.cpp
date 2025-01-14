#include "FilterStringsTest.h"

#include <QCheckBox>
#include <QListWidget>
#include <QSignalSpy>
#include <QTest>

#include <wble/FilterStrings.h>

void FilterStringsTest::initTestCase()
{
    testEntriesList_ = QStringList{QString::fromLatin1("a"), QString::fromLatin1("b"),
                                   QString::fromLatin1("c"), QString::fromLatin1("d")};
}

void FilterStringsTest::testToggling()
{
    FilterStrings filter(QString::fromLatin1(""), testEntriesList_);
    auto* listWidget{filter.findChild<QListWidget*>()};
    auto* selectAll{filter.findChild<QCheckBox*>()};
    QCOMPARE(listWidget->isEnabled(), true);
    QCOMPARE(selectAll->isEnabled(), true);

    filter.setChecked(false);
    QCOMPARE(listWidget->isEnabled(), false);
    QCOMPARE(selectAll->isEnabled(), false);
}

void FilterStringsTest::testSelectAllToggling()
{
    const FilterStrings filter(QString::fromLatin1(""), testEntriesList_);
    QSignalSpy spy(&filter, &FilterStrings::newStringFilter);

    auto* selectAll{filter.findChild<QCheckBox*>()};
    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(testEntriesList_)});

    selectAll->toggle();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{})});
}

void FilterStringsTest::testListItemChecking()
{
    const FilterStrings filter(QString::fromLatin1(""), testEntriesList_);
    QSignalSpy spy(&filter, &FilterStrings::newStringFilter);
    const auto* listWidget{filter.findChild<QListWidget*>()};
    const int itemPos{
        static_cast<int>(testEntriesList_.indexOf(QStringLiteral("b")))};
    const auto* item{listWidget->item(itemPos)};
    const QRect itemRect = listWidget->visualItemRect(item);
    QTest::mouseClick(listWidget->viewport(), Qt::LeftButton, Qt::NoModifier,
                      itemRect.center());

    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{"b"})});
    QCOMPARE(spy.count(), NO_SIGNAL);

    QApplication::processEvents();
    QTest::mouseClick(listWidget->viewport(), Qt::LeftButton, Qt::NoModifier,
                      itemRect.center());
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QCOMPARE(spy.takeFirst(), {QVariant(QStringList{})});
}
