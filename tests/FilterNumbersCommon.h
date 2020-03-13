#ifndef FILTERNUMBERSCOMMON_H
#define FILTERNUMBERSCOMMON_H

#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>

#include "DoubleSlider.h"

namespace FilterNumbersCommon
{

static constexpr int NO_SIGNAL {0};
static constexpr int SIGNAL_RECEIVED {1};

template <class T, typename U>
void checkToggling(U fromValue, U toValue)
{
    T filter("", fromValue, toValue);
    QList<QLineEdit*> lineEdits = filter.template findChildren<QLineEdit*>();
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), true);

    filter.setChecked(false);
    for (const auto& lineEdit : lineEdits)
        QCOMPARE(lineEdit->isEnabled(), false);
}

std::tuple<QLineEdit*, QLineEdit*> getLineEdits(QList<QLineEdit*> lineEdits,
                                                int fromValue,
                                                int toValue);

template <class T, typename U>
void checkChangingEditLinesValues(U fromValue, U toValue)
{
    T filter("", fromValue, toValue);
    auto lineEdits = filter.template findChildren<QLineEdit*>();
    Q_ASSERT(lineEdits.count() == 2);
    auto [fromLineEdit, toLineEdit] = getLineEdits(lineEdits,
                                                   static_cast<int>(fromValue),
                                                   static_cast<int>(toValue));

    QSignalSpy spy(&filter, &T::newNumericFilter);
    const U newMin = 20.;
    fromLineEdit->setText(QLocale::system().toString(newMin));
    QTest::keyClick(fromLineEdit, Qt::Key_Enter);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedValues {newMin, toValue};
    QCOMPARE(spy.takeFirst(), expectedValues);

    const U newMax = 50.;
    toLineEdit->setText(QLocale::system().toString(newMax));
    QTest::keyClick(toLineEdit, Qt::Key_Enter);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    expectedValues = {newMin, newMax};
    QCOMPARE(spy.takeFirst(), expectedValues);

    QApplication::processEvents();
    auto doubleSlider = filter.template findChild<DoubleSlider*>();
    QCOMPARE(doubleSlider->getCurrentMin(), newMin);
    QCOMPARE(doubleSlider->getCurrentMax(), newMax);
}

template <class T, typename U>
void checkReactionForMovingDoubleSlider(U fromValue, U toValue)
{
    T filter("", fromValue, toValue);
    auto doubleSlider = filter.template findChild<DoubleSlider*>();
    QSignalSpy spy(&filter, &T::newNumericFilter);
    const U newMin = 20.;
    Q_EMIT doubleSlider->currentMinChanged(newMin);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    QList<QVariant> expectedValues {newMin, toValue};
    QCOMPARE(spy.takeFirst(), expectedValues);

    const U newMax = 50.;
    Q_EMIT doubleSlider->currentMaxChanged(newMax);
    QCOMPARE(spy.count(), SIGNAL_RECEIVED);
    expectedValues = {newMin, newMax};
    QCOMPARE(spy.takeFirst(), expectedValues);
}

};

#endif // FILTERNUMBERSCOMMON_H
