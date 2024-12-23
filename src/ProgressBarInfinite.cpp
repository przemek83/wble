#include <wble/ProgressBarInfinite.h>
#include "Utilities.h"

ProgressBarInfinite::ProgressBarInfinite(QString title, QWidget* parent)
    : ProgressBar{std::move(title), parent}
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

void ProgressBarInfinite::reset()
{
    progressCounter_ = 0;
    ProgressBar::reset();
}

void ProgressBarInfinite::paintProgressBar(QPainter& painter)
{
    const auto [firstAngle, secondAngle]{
        utilities::getStartingAnglesInfinite(progressCounter_)};
    const int spanAngle{utilities::getSpanAngleInfinite()};

    painter.drawArc(getArcRectangle(), firstAngle, spanAngle);
    painter.drawArc(getArcRectangle(), secondAngle, spanAngle);
}

void ProgressBarInfinite::timerEvent([[maybe_unused]] QTimerEvent* event)
{
    constexpr int fullRotation{100};
    ++progressCounter_;
    progressCounter_ %= fullRotation;
    update();
}
