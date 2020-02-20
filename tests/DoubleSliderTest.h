#ifndef CONSTANTSTEST_H
#define CONSTANTSTEST_H

#include <QObject>

class DoubleSlider;

/**
 * @brief Unit test for Constants class.
 */
class DoubleSliderTest: public QObject
{
    Q_OBJECT
private slots:
    void testSettingCurrentValues();

    void testEmittingCurrentMinChanged();

    void testEmittingCurrentMaxChanged();

    void testSettingInvalidCurrentMin();

    void testSettingInvalidCurrentMax();

    void testMovingLeftHandle();

private:
    void moveHandle(DoubleSlider& slider, QPoint from, QPoint to) const;

    static constexpr int MIN {-100};
    static constexpr int MAX {100};
    static constexpr int SLIDER_WIDTH {MAX - MIN};
    static constexpr int SLIDER_HEIGHT {SLIDER_WIDTH / 5};
};

#endif // CONSTANTSTEST_H
