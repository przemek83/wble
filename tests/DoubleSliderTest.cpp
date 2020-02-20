#include "DoubleSliderTest.h"

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
