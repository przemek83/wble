#include "FilterIntegersTest.h"

#include <QDebug>
#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "DoubleSlider.h"

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
    const double newMin {20.};
    fromLineEdit->setText(QLocale::system().toString(newMin));
    QTest::keyClick(fromLineEdit, Qt::Key_Enter);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedValues {newMin, toValue_};
    QCOMPARE(spy.takeFirst(), expectedValues);

    const double newMax {50.};
    toLineEdit->setText(QLocale::system().toString(newMax));
    QTest::keyClick(toLineEdit, Qt::Key_Enter);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    expectedValues = {newMin, newMax};
    QCOMPARE(spy.takeFirst(), expectedValues);

    QApplication::processEvents();
    auto doubleSlider = filter.findChild<DoubleSlider*>();
    QCOMPARE(doubleSlider->getCurrentMin(), newMin);
    QCOMPARE(doubleSlider->getCurrentMax(), newMax);
}

void FilterIntegersTest::testReactionForMovingDoubleSlider()
{
    FilterIntegers filter("", fromValue_, toValue_);
    auto doubleSlider = filter.findChild<DoubleSlider*>();
    QSignalSpy spy(&filter, &FilterIntegers::newNumericFilter);
    const double newMin {20.};
    Q_EMIT doubleSlider->currentMinChanged(newMin);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedValues {newMin, toValue_};
    QCOMPARE(spy.takeFirst(), expectedValues);

    const double newMax {50.};
    Q_EMIT doubleSlider->currentMaxChanged(newMax);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    expectedValues = {newMin, newMax};
    QCOMPARE(spy.takeFirst(), expectedValues);
}
