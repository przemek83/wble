#include "ProgressBarCounter.h"

ProgressBarCounter::ProgressBarCounter(QString title,
                                       int maxValue,
                                       QWidget* parent) :
    ProgressBar(title, parent),
    maxValue_(maxValue)
{

}

void ProgressBarCounter::stop()
{
    currentPercent_ = 0;
    ProgressBar::stop();
}

int ProgressBarCounter::getCurrentPercent()
{
    return currentPercent_;
}

void ProgressBarCounter::updateProgress(int newValue)
{
    int newPercent = lround(newValue * 1.0 / maxValue_ * 100);
    if (newPercent > currentPercent_)
    {
        currentPercent_ = newPercent;
        update();
        QApplication::processEvents();
    }
}

void ProgressBarCounter::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    std::unique_ptr<QPainter> painter = getPainter();
    constexpr int startAngle {QUARTER_CIRCLE_ANGLE * FULL_DEGREE};
    const int spanAngle = lround(-currentPercent_ * HUNDREDTH_OF_FULL_CIRCLE * FULL_DEGREE);
    painter->drawArc(arcRectangle_, startAngle, spanAngle);
    painter->drawText(arcRectangle_,
                      Qt::AlignCenter,
                      QString::number(currentPercent_, 'f', 0) + "%");

    paintTitle(painter);
}
