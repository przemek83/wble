#include "DoubleSliderTest.h"

#include <QSignalSpy>
#include <QtTest/QtTest>

#include "DoubleSlider.h"

void DoubleSliderTest::testSettingCurrentValues()
{
    const double min {-100};
    const double max {100};
    DoubleSlider slider(min, max);
    QCOMPARE(slider.getMin(), min);
    QCOMPARE(slider.getMax(), max);
    QCOMPARE(slider.getCurrentMin(), min);
    QCOMPARE(slider.getCurrentMax(), max);

    slider.setCurrentMin(min * 2);
    QCOMPARE(slider.getMin(), min);
    QCOMPARE(slider.getCurrentMin(), min * 2);

    slider.setCurrentMin(max * 2);
    QCOMPARE(slider.getMax(), max);
    QCOMPARE(slider.getCurrentMax(), max * 2);
}

void DoubleSliderTest::testEmittingCurrentMinChanged()
{
    const double min {-100};
    const double max {100};
    DoubleSlider slider(min, max);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);
    QCOMPARE(spyMin.count(), 0);
    QCOMPARE(spyMax.count(), 0);

    slider.setCurrentMin(min * 2);
    QCOMPARE(slider.getCurrentMin(), min * 2);
    QCOMPARE(spyMin.count(), 1);
    QCOMPARE(spyMax.count(), 0);
    QList<QVariant> arguments = spyMin.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    QCOMPARE(arguments.at(0).toDouble(), min * 2);
}

void DoubleSliderTest::testEmittingCurrentMaxChanged()
{

}
