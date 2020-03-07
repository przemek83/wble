#include "FilterIntegersTest.h"

#include <QDebug>
#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "FilterIntegers.h"

void FilterIntegersTest::testToggling()
{
    FilterIntegers filter("", 0., 100.);
    auto lineEdits = filter.findChildren<QLineEdit*>();
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), true);

    filter.setChecked(false);
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), false);
}
