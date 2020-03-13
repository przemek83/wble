#include "ProgressBarCounter.h"

ProgressBarCounter::ProgressBarCounter(QString title,
                                       int maxValue,
                                       QWidget* parent) :
    ProgressBar(std::move(title), parent),
    maxValue_(maxValue)
{
}

void ProgressBarCounter::reset()
{
    currentPercent_ = 0;
    ProgressBar::reset();
}

void ProgressBarCounter::updateProgress(int newValue)
{
    if (!isRunning())
        start();

    const int newPercent =
        std::lround(static_cast<double>(newValue) / maxValue_ * 100.0);

    currentPercent_ = newPercent;
    update();
    QApplication::processEvents();
}

void ProgressBarCounter::paintProgressBar(QPainter& painter)
{
    constexpr int startAngle {QUARTER_CIRCLE_ANGLE * FULL_DEGREE};
    const int spanAngle =
        lround(-currentPercent_ * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE);
    painter.drawArc(arcRectangle_, startAngle, spanAngle);
    painter.drawText(arcRectangle_,
                     Qt::AlignCenter,
                     QString::number(currentPercent_, 'f', 0) + "%");
}
