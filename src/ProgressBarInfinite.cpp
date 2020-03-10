#include "ProgressBarInfinite.h"

#include <limits>

ProgressBarInfinite::ProgressBarInfinite(QString title, QWidget* parent) :
    ProgressBar(title, parent)
{
}

void ProgressBarInfinite::start()
{
    timerId_ = startTimer(TIMER_DEFAULT_INTERVAL);
    ProgressBar::start();
}

void ProgressBarInfinite::stop()
{
    killTimer(timerId_);
    timerId_ = 0;
    ProgressBar::stop();
}

void ProgressBarInfinite::paintProgress(QPainter& painter)
{
    constexpr int step {45};
    int startAngle =
        lround(progressCounter_ * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE);
    constexpr const int spanAngle = -step * FULL_DEGREE;
    painter.drawArc(arcRectangle_, startAngle, spanAngle);
    startAngle =
        lround((HALF_CIRCLE_ANGLE + progressCounter_ * HUNDREDTH_OF_FULL_CIRCLE) * FULL_DEGREE);
    painter.drawArc(arcRectangle_, startAngle, spanAngle);
}

void ProgressBarInfinite::timerEvent([[maybe_unused]] QTimerEvent* event)
{
    constexpr int fullRotation {100};
    progressCounter_++;
    progressCounter_ %= fullRotation;
    update();
}
