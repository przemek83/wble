#include "FilterIntegersTest.h"

#include <QDebug>
#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "Utilities.h"

#include "FilterIntegers.h"

void FilterIntegersTest::testToggling()
{
    FilterIntegers filter("", fromValue_, toValue_);
    auto lineEdits = filter.findChildren<QLineEdit*>();
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), true);

    filter.setChecked(false);
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), false);
}

std::tuple<QLineEdit*, QLineEdit*>
FilterIntegersTest::getLineEdits(QList<QLineEdit*> lineEdits) const
{
    const int firstValue =
        QLocale::system().toInt(lineEdits.first()->text());
    QLineEdit* fromEdit = (firstValue == fromValue_ ?
                           lineEdits.first() : lineEdits.last());
    QLineEdit* toEdit = (firstValue == toValue_ ?
                         lineEdits.first() : lineEdits.last());
    return {fromEdit, toEdit};
}

void FilterIntegersTest::testChangingEditLinesValues()
{
    FilterIntegers filter("", fromValue_, toValue_);
    auto lineEdits = filter.findChildren<QLineEdit*>();
    Q_ASSERT(lineEdits.count() == 2);
    auto [fromLineEdit, toLineEdit] = getLineEdits(lineEdits);

    QSignalSpy spy(&filter, &FilterIntegers::newNumericFilter);
    fromLineEdit->setText("20");
    QTest::keyClick(fromLineEdit, Qt::Key_Enter);
    QApplication::processEvents();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedValues {20, 100};
    QCOMPARE(spy.takeFirst(), expectedValues);

    toLineEdit->setText("50");
    QTest::keyClick(fromLineEdit, Qt::Key_Enter);
    QApplication::processEvents();
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    expectedValues = {20, 50};
    QCOMPARE(spy.takeFirst(), expectedValues);
}
