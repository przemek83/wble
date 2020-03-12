#ifndef DOUBLESLIDERTEST
#define DOUBLESLIDERTEST

#include <QObject>

class DoubleSlider;

class DoubleSliderTest: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();

    void testSettingCurrentValues();

    void testEmittingCurrentMinChanged();

    void testEmittingCurrentMaxChanged();

    void testSettingInvalidCurrentMin();

    void testSettingInvalidCurrentMax();

    void testMovingLeftHandle();

    void testMovingRightHandle();

    void testMovingBothHandlesTogether();

private:
    void moveHandle(DoubleSlider& slider, QPoint from, QPoint to) const;

    static constexpr int MIN {-100};
    static constexpr int MAX {100};
    static constexpr int SLIDER_WIDTH {MAX - MIN};
    static constexpr int SLIDER_HEIGHT {SLIDER_WIDTH / 5};

    static constexpr int NO_SIGNAL {0};
    static constexpr int SIGNAL_RECEIVED {1};
};

#endif // DOUBLESLIDERTEST
