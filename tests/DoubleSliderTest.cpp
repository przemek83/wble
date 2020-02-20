#include "DoubleSliderTest.h"

#include <QSignalSpy>
#include <QtTest/QtTest>

#include "DoubleSlider.h"

void DoubleSliderTest::testSettingCurrentValues()
{
    DoubleSlider slider(min_, max_);
    QCOMPARE(slider.getMin(), min_);
    QCOMPARE(slider.getMax(), max_);
    QCOMPARE(slider.getCurrentMin(), min_);
    QCOMPARE(slider.getCurrentMax(), max_);

    slider.setCurrentMin(min_ / 2);
    QCOMPARE(slider.getMin(), min_);
    QCOMPARE(slider.getCurrentMin(), min_ / 2);

    slider.setCurrentMax(max_ / 2);
    QCOMPARE(slider.getMax(), max_);
    QCOMPARE(slider.getCurrentMax(), max_ / 2);
}

void DoubleSliderTest::testEmittingCurrentMinChanged()
{
    DoubleSlider slider(min_, max_);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    slider.setCurrentMin(min_ / 2);
    QCOMPARE(spyMin.count(), 1);
    QCOMPARE(spyMax.count(), 0);
    QList<QVariant> arguments = spyMin.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    QCOMPARE(arguments.at(0).toDouble(), min_ / 2);
}

void DoubleSliderTest::testEmittingCurrentMaxChanged()
{
    DoubleSlider slider(min_, max_);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    slider.setCurrentMax(max_ / 2);
    QCOMPARE(spyMin.count(), 0);
    QCOMPARE(spyMax.count(), 1);
    QList<QVariant> arguments = spyMax.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    QCOMPARE(arguments.at(0).toDouble(), max_ / 2);
}

void DoubleSliderTest::testSettingInvalidCurrentMin()
{
    DoubleSlider slider(min_, max_);
    slider.setCurrentMin(min_ - 1);
    QCOMPARE(slider.getCurrentMin(), min_);

    slider.setCurrentMin(max_ + 1);
    QCOMPARE(slider.getCurrentMin(), max_);
}

void DoubleSliderTest::testSettingInvalidCurrentMax()
{
    DoubleSlider slider(min_, max_);
    slider.setCurrentMax(max_ + 1);
    QCOMPARE(slider.getCurrentMax(), max_);

    slider.setCurrentMax(min_ - 1);
    QCOMPARE(slider.getCurrentMax(), min_);
}
