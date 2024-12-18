#include <wble/ProgressBarCounter.h>

ProgressBarCounter::ProgressBarCounter(QString title, int maxValue,
                                       QWidget* parent)
    : ProgressBar(std::move(title), parent), maxValue_(maxValue)
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

    const int newPercent{static_cast<int>(
        std::lround((static_cast<double>(newValue) / maxValue_) * 100.0))};

    currentPercent_ = newPercent;
    update();
    QApplication::processEvents();
}

void ProgressBarCounter::paintProgressBar(QPainter& painter)
{
    constexpr int startAngle{QUARTER_CIRCLE_ANGLE * FULL_DEGREE};
    const int spanAngle{static_cast<int>(std::lround(
        -currentPercent_ * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE))};
    painter.drawArc(getArcRectangle(), startAngle, spanAngle);
    painter.drawText(getArcRectangle(), Qt::AlignCenter,
                     QString::number(currentPercent_, 'f', 0) + "%");
}
