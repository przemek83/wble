#include "FilterNamesTest.h"

#include <QCheckBox>
#include <QListWidget>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "FilterNames.h"

void FilterNamesTest::testToggling()
{
    FilterNames filter(" ", {"a", "b", "c", "d"});
    auto listWidget = filter.findChild<QListWidget*>();
    auto selectAll = filter.findChild<QCheckBox*>();
    QCOMPARE(listWidget->isEnabled(), true);
    QCOMPARE(selectAll->isEnabled(), true);

    filter.setChecked(false);

    QCOMPARE(listWidget->isEnabled(), false);
    QCOMPARE(selectAll->isEnabled(), false);
}
