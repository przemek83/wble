#include "DoubleSliderTest.h"

#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "DoubleSlider.h"

void DoubleSliderTest::testSettingCurrentValues()
{
    DoubleSlider slider(MIN, MAX);
    QCOMPARE(slider.getMin(), MIN);
    QCOMPARE(slider.getMax(), MAX);
    QCOMPARE(slider.getCurrentMin(), MIN);
    QCOMPARE(slider.getCurrentMax(), MAX);

    slider.setCurrentMin(MIN / 2);
    QCOMPARE(slider.getMin(), MIN);
    QCOMPARE(slider.getCurrentMin(), MIN / 2);

    slider.setCurrentMax(MAX / 2);
    QCOMPARE(slider.getMax(), MAX);
    QCOMPARE(slider.getCurrentMax(), MAX / 2);
}

void DoubleSliderTest::testEmittingCurrentMinChanged()
{
    DoubleSlider slider(MIN, MAX);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    slider.setCurrentMin(MIN / 2);
    QCOMPARE(spyMin.count(), 1);
    QCOMPARE(spyMax.count(), 0);
    QList<QVariant> arguments = spyMin.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    QCOMPARE(arguments.at(0).toDouble(), MIN / 2);
}

void DoubleSliderTest::testEmittingCurrentMaxChanged()
{
    DoubleSlider slider(MIN, MAX);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    slider.setCurrentMax(MAX / 2);
    QCOMPARE(spyMin.count(), 0);
    QCOMPARE(spyMax.count(), 1);
    QList<QVariant> arguments = spyMax.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    QCOMPARE(arguments.at(0).toDouble(), MAX / 2);
}

void DoubleSliderTest::testSettingInvalidCurrentMin()
{
    DoubleSlider slider(MIN, MAX);
    slider.setCurrentMin(MIN - 1);
    QCOMPARE(slider.getCurrentMin(), MIN);

    slider.setCurrentMin(MAX + 1);
    QCOMPARE(slider.getCurrentMin(), MAX);
    QCOMPARE(slider.getCurrentMax(), MAX);
}

void DoubleSliderTest::testSettingInvalidCurrentMax()
{
    DoubleSlider slider(MIN, MAX);
    slider.setCurrentMax(MAX + 1);
    QCOMPARE(slider.getCurrentMax(), MAX);

    slider.setCurrentMax(MIN - 1);
    QCOMPARE(slider.getCurrentMax(), MIN);
    QCOMPARE(slider.getCurrentMin(), MIN);
}

void DoubleSliderTest::testMovingLeftHandle()
{
    DoubleSlider slider(MIN, MAX);
    slider.resize(SLIDER_WIDTH, SLIDER_HEIGHT);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    const QPoint startPoint(0, 0);
    const QPoint endPoint(SLIDER_WIDTH / 2, 0);
    moveHandle(slider, startPoint, endPoint);

    QCOMPARE(slider.getCurrentMin(), 0);
    QCOMPARE(slider.getCurrentMax(), MAX);

    QCOMPARE(spyMin.count(), 1);
    QCOMPARE(spyMax.count(), 0);
    QList<QVariant> arguments = spyMin.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    const int middleOfRange {(MAX + MIN) / 2};
    QCOMPARE(arguments.at(0).toDouble(), middleOfRange);
}

void DoubleSliderTest::testMovingRightHandle()
{
    DoubleSlider slider(MIN, MAX);
    slider.resize(SLIDER_WIDTH, SLIDER_HEIGHT);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    const QPoint startPoint(SLIDER_WIDTH, 0);
    const QPoint endPoint(SLIDER_WIDTH / 2, 0);
    moveHandle(slider, startPoint, endPoint);

    QCOMPARE(slider.getCurrentMin(), MIN);
    QCOMPARE(slider.getCurrentMax(), 0);

    QCOMPARE(spyMin.count(), 0);
    QCOMPARE(spyMax.count(), 1);
    QList<QVariant> arguments = spyMax.takeFirst();
    QCOMPARE(arguments.at(0).type(), QMetaType::Double);
    const int middleOfRange {(MAX + MIN) / 2};
    QCOMPARE(arguments.at(0).toDouble(), middleOfRange);
}

void DoubleSliderTest::testMovingBothHandlesTogether()
{
    DoubleSlider slider(MIN, MAX);
    slider.resize(SLIDER_WIDTH, SLIDER_HEIGHT);

    // Move left handle from MIN to middle of slider range.
    const QPoint startPointMin(0, 0);
    const QPoint endPoinMin(SLIDER_WIDTH / 2, 0);
    moveHandle(slider, startPointMin, endPoinMin);

    QSignalSpy spyMin(&slider, &DoubleSlider::currentMinChanged);
    QSignalSpy spyMax(&slider, &DoubleSlider::currentMaxChanged);

    // Move right handle from MAX to left side.
    const QPoint startPointMax(SLIDER_WIDTH, 0);
    const QPoint endPointMax(0, 0);
    moveHandle(slider, startPointMax, endPointMax);

    QCOMPARE(spyMin.count(), 1);
    QCOMPARE(spyMax.count(), 1);
    QCOMPARE(slider.getCurrentMin(), MIN);
    QCOMPARE(slider.getCurrentMax(), MIN);

    QList<QVariant> spyMaxArguments = spyMax.takeFirst();
    QCOMPARE(spyMaxArguments.at(0).type(), QMetaType::Double);
    QCOMPARE(spyMaxArguments.at(0).toDouble(), MIN);

    QList<QVariant> spyMinArguments = spyMin.takeFirst();
    QCOMPARE(spyMinArguments.at(0).type(), QMetaType::Double);
    QCOMPARE(spyMinArguments.at(0).toDouble(), MIN);
}

void DoubleSliderTest::moveHandle(DoubleSlider& slider, QPoint from, QPoint to) const
{
    QTest::mousePress(&slider, Qt::LeftButton, Qt::NoModifier, from);
    QMouseEvent initialEvent(QEvent::MouseMove, from, Qt::NoButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(&slider, &initialEvent);
    QMouseEvent moveEvent(QEvent::MouseMove, to, Qt::NoButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(&slider, &moveEvent);
    QTest::mouseRelease(&slider, Qt::LeftButton, Qt::NoModifier, to);
}
