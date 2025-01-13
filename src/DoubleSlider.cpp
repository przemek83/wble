#include <wble/DoubleSlider.h>

#include <cmath>

#include <qdrawutil.h>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionSlider>

#include "Utilities.h"

DoubleSlider::DoubleSlider(double min, double max, QWidget* parent)
    : QSlider(parent),
      min_{min},
      max_{max},
      currentMin_{min},
      currentMax_{max},
      lastEmittedMin_{min},
      lastEmittedMax_{max}

{
    setOrientation(Qt::Horizontal);

    setMouseTracking(true);

    setMinimum(0);
    setMaximum(MAX_PERCENT);

    setHandleRect();
}

DoubleSlider::DoubleSlider(double min, double max)
    : DoubleSlider(min, max, nullptr)
{
}

double DoubleSlider::getCurrentMin() const { return currentMin_; }

double DoubleSlider::getCurrentMax() const { return currentMax_; }

double DoubleSlider::getMin() const { return min_; }

double DoubleSlider::getMax() const { return max_; }

void DoubleSlider::setCurrentMin(double currentMinToSet)
{
    if (utilities::doublesAreEqual(currentMin_, currentMinToSet))
        return;

    currentMin_ = getNormalizedValue(currentMinToSet);
    if (currentMin_ > currentMax_)
        setCurrentMax(currentMin_);

    update();
}

void DoubleSlider::setCurrentMax(double currentMaxToSet)
{
    if (utilities::doublesAreEqual(currentMax_, currentMaxToSet))
        return;

    currentMax_ = getNormalizedValue(currentMaxToSet);
    if (currentMax_ < currentMin_)
        setCurrentMin(currentMax_);

    update();
}

double DoubleSlider::getNormalizedValue(double value) const
{
    if ((value <= max_) && (value >= min_))
        return value;

    if (value > max_)
        return max_;

    return min_;
}

int DoubleSlider::getMousePosition(const QMouseEvent* event) const
{
    const QRect innerRect{getInnerRectangle()};
    const int sliderBarWidth{innerRect.width() - innerRect.x()};

    // Handle drawing rectangle is shifted according to position on handle bar.
    const double shiftRatio{(event->position().x() / sliderBarWidth) - 0.5};
    const int shiftInPixels{
        static_cast<int>(std::round(handleRect_.width() * shiftRatio))};
    const int pos{QStyle::sliderValueFromPosition(
        0, MAX_PERCENT, static_cast<int>(event->position().x()) + shiftInPixels,
        sliderBarWidth)};

    return pos;
}

void DoubleSlider::mousePressEvent([[maybe_unused]] QMouseEvent* ev)
{
    moving_ = Handle::NONE;
}

void DoubleSlider::mouseReleaseEvent(QMouseEvent* ev)
{
    moving_ = Handle::NONE;
    mouseMoveEvent(ev);
    update();
}

void DoubleSlider::changeEvent(QEvent* e)
{
    QSlider::changeEvent(e);

    if (e->type() == QEvent::StyleChange)
        setHandleRect();
}

bool DoubleSlider::mouseIsOnHandle(int mousePosX, int handlePos) const
{
    const QRect innerRect{getInnerRectangle()};
    const int sliderBarWidth{innerRect.width() - innerRect.x()};
    const int handlePosX{QStyle::sliderPositionFromValue(
        0, MAX_PERCENT, handlePos, sliderBarWidth)};

    // Handle drawing rectangle is shifted according to position on handle bar:
    // - on left edge handle rectangle is placed between min and handle width.
    // - on right edge handle rectangle is placed between max - handle width and
    // max.
    // - on center handle rectangle is placed between center - handle width / 2
    // and center + handle width / 2.
    const double shiftRatio{static_cast<double>(handlePos) / MAX_PERCENT};
    return (mousePosX <=
            (handlePosX + (handleRect_.width() * (1 - shiftRatio)))) &&
           (mousePosX >= (handlePosX - (handleRect_.width() * shiftRatio)));
}

void DoubleSlider::mouseMoveEvent(QMouseEvent* ev)
{
    if ((ev->buttons() & Qt::LeftButton) == 0U)
    {
        moving_ = Handle::NONE;
        return;
    }

    const int newPosition{getMousePosition(ev)};
    const int minX{getHandlePosition(Handle::LEFT)};
    const int maxX{getHandlePosition(Handle::RIGHT)};

    const bool onMinHandle{
        mouseIsOnHandle(static_cast<int>(ev->position().x()), minX)};
    const bool onMaxHandle{
        mouseIsOnHandle(static_cast<int>(ev->position().x()), maxX)};

    const double range{max_ - min_};
    const double newCurrent{
        ((static_cast<double>(newPosition) / MAX_PERCENT) * range) + min_};

    if ((moving_ == Handle::LEFT) || ((moving_ == Handle::NONE) && onMinHandle))
    {
        setCurrentMin(newCurrent);
        moving_ = Handle::LEFT;
    }

    if ((moving_ == Handle::RIGHT) ||
        ((moving_ == Handle::NONE) && onMaxHandle))
    {
        setCurrentMax(newCurrent);
        moving_ = Handle::RIGHT;
    }

    if (!utilities::doublesAreEqual(lastEmittedMin_, currentMin_))
    {
        lastEmittedMin_ = currentMin_;
        Q_EMIT currentMinChanged(currentMin_);
    }

    if (!utilities::doublesAreEqual(lastEmittedMax_, currentMax_))
    {
        lastEmittedMax_ = currentMax_;
        Q_EMIT currentMaxChanged(currentMax_);
    }
}

int DoubleSlider::getHandlePosition(Handle handle) const
{
    const double range{max_ - min_};
    double currentValue{0};
    if (handle == Handle::LEFT)
        currentValue = currentMin_;
    else
        currentValue = currentMax_;
    currentValue -= min_;

    return static_cast<int>(std::round((currentValue / range) * MAX_PERCENT));
}

void DoubleSlider::drawSliderBar(QPainter& painter) const
{
    const QRect innerRect{getInnerRectangle()};

    const int handleHight{
        static_cast<int>(innerRect.height() * BAR_HEIGHT_RATIO)};
    const QRect plain{QRect(
        innerRect.x() + (handleRect_.width() / 4), innerRect.y() + handleHight,
        innerRect.width() - (handleRect_.width() / 2), handleHight)};
    ::qDrawPlainRect(&painter, plain, palette().color(QPalette::Dark));
}

int DoubleSlider::getHandleMiddlePosX(int handlePos, int handleWidth, int span)
{
    const int handlePosX{
        QStyle::sliderPositionFromValue(0, MAX_PERCENT, handlePos, span)};
    const double handleShiftRatio{handlePos / static_cast<double>(MAX_PERCENT)};
    const int handleMiddleX{handlePosX +
                            static_cast<int>(std::round(
                                ((1 - handleShiftRatio) * handleWidth) / 2.))};
    return handleMiddleX;
}

void DoubleSlider::setHandleRect()
{
    QStyleOptionSlider defaultStyle;
    QSlider::initStyleOption(&defaultStyle);
    handleRect_ = style()->subControlRect(QStyle::CC_Slider, &defaultStyle,
                                          QStyle::SC_SliderHandle, this);
}

void DoubleSlider::drawSliderBarBetweenHandles(QPainter& painter) const
{
    const QRect barRect{getBarRectangle()};
    const QBrush brush{palette().brush(QPalette::Dark)};
    ::qDrawShadePanel(&painter, barRect, palette(), true, 1, &brush);
}

QStyleOptionSlider DoubleSlider::getHandleStyle(bool moving, int position) const
{
    QStyleOptionSlider handleStyle;
    initStyleOption(&handleStyle);
    handleStyle.sliderPosition = position;
    if (moving)
        handleStyle.state = QStyle::State_Raised;
    handleStyle.subControls = QStyle::SC_SliderHandle;
    return handleStyle;
}

void DoubleSlider::drawHandles(QPainter& painter) const
{
    const QStyleOptionSlider leftStyle{getHandleStyle(
        moving_ == Handle::LEFT, getHandlePosition(Handle::LEFT))};
    style()->drawComplexControl(QStyle::CC_Slider, &leftStyle, &painter, this);

    const QStyleOptionSlider rightStyle{getHandleStyle(
        moving_ == Handle::RIGHT, getHandlePosition(Handle::RIGHT))};
    style()->drawComplexControl(QStyle::CC_Slider, &rightStyle, &painter, this);
}

void DoubleSlider::paintEvent(QPaintEvent* ev)
{
    if (utilities::doublesAreEqual(min_, max_))
        return;

    QPainter painter(this);
    painter.setClipRegion(ev->region());

    drawSliderBar(painter);
    drawSliderBarBetweenHandles(painter);
    drawHandles(painter);
}

QRect DoubleSlider::getInnerRectangle() const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    return defaultStyle.rect;
}

QRect DoubleSlider::getBarRectangle() const
{
    const QRect innerRect{getInnerRectangle()};

    const int barHeight{
        static_cast<int>(std::round(innerRect.height() * BAR_HEIGHT_RATIO))};

    const int leftHandlePosition{getHandlePosition(Handle::LEFT)};
    const int rightHandlePosition{getHandlePosition(Handle::RIGHT)};

    const int leftHandleMiddleX{
        getHandleMiddlePosX(leftHandlePosition, handleRect_.width(),
                            innerRect.width() - innerRect.x())};

    const int rightHandleMiddleX{
        getHandleMiddlePosX(rightHandlePosition, handleRect_.width(),
                            innerRect.width() - innerRect.x())};

    const QRect barRect{QRect(
        innerRect.x() + leftHandleMiddleX, innerRect.y() + barHeight,
        (innerRect.x() + rightHandleMiddleX) - leftHandleMiddleX, barHeight)};

    return barRect;
}
