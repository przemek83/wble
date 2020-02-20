#include "DoubleSlider.h"

#include <cmath>

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionSlider>
#include <qdrawutil.h>

namespace
{
bool doublesAreEqual(double left, double right)
{
    static const double qtDoublePrecision {1e-12};
    return std::abs(left - right) <=
           qtDoublePrecision * std::max({ 1.0, std::abs(left), std::abs(right) });
}
} // namespace

DoubleSlider::DoubleSlider(double min, double max, QWidget* parent) :
    QSlider(parent), min_(min), max_(max),
    currentMin_(min), currentMax_(max),
    lastEmittedMin_(min),  lastEmittedMax_(max)

{
    setOrientation(Qt::Horizontal);

    setMouseTracking(true);

    setMinimum(0);
    setMaximum(100);

    setHandleRect();
}

double DoubleSlider::getCurrentMin() const
{
    return currentMin_;
}

double DoubleSlider::getCurrentMax() const
{
    return currentMax_;
}

double DoubleSlider::getMin() const
{
    return min_;
}

double DoubleSlider::getMax() const
{
    return max_;
}

void DoubleSlider::setCurrentMin(double currentMinToSet)
{
    if (currentMinToSet >= min_ && !doublesAreEqual(currentMin_, currentMinToSet))
    {
        currentMin_ = currentMinToSet;
        if (!doublesAreEqual(lastEmittedMin_, currentMinToSet))
        {
            lastEmittedMin_ = currentMinToSet;
            Q_EMIT currentMinChanged(currentMinToSet);
        }
    }

    if (currentMinToSet > currentMax_)
    {
        setCurrentMax(currentMinToSet);
    }

    update();
}

void DoubleSlider::setCurrentMax(double currentMaxToSet)
{
    if (currentMaxToSet <= max_ && !doublesAreEqual(currentMax_, currentMaxToSet))
    {
        currentMax_ = currentMaxToSet;
        if (!doublesAreEqual(lastEmittedMax_, currentMaxToSet))
        {
            lastEmittedMax_ = currentMaxToSet;
            Q_EMIT currentMaxChanged(currentMaxToSet);
        }
    }

    if (currentMaxToSet < currentMin_)
    {
        setCurrentMin(currentMaxToSet);
    }

    update();
}

int DoubleSlider::getMousePosition(QMouseEvent* event) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);
    const int sliderBarWidth {innerRect.width() - innerRect.x()};

    // Handle drawing rectangle is shifted according to position on handle bar.
    const double shiftRatio =
        static_cast<double>(event->x()) / sliderBarWidth - 0.5;
    const int shiftInPixels =
        static_cast<int>(std::round(handleRect_.width() * shiftRatio));
    const int pos = QStyle::sliderValueFromPosition(0,
                                                    MAX_PERCENT,
                                                    event->x() + shiftInPixels,
                                                    sliderBarWidth);
    return pos;
}

void DoubleSlider::mousePressEvent([[maybe_unused]] QMouseEvent* event)
{
    moving_ = Handle::NONE;
}

void DoubleSlider::mouseReleaseEvent(QMouseEvent* event)
{
    moving_ = Handle::NONE;
    mouseMoveEvent(event);
    update();
}

void DoubleSlider::changeEvent(QEvent* event)
{
    QSlider::changeEvent(event);

    if (event->type() == QEvent::StyleChange)
    {
        setHandleRect();
    }
}

bool DoubleSlider::mouseIsOnHandle(int mousePosX, int handlePos) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);
    const int sliderBarWidth {innerRect.width() - innerRect.x()};
    int handlePosX = QStyle::sliderPositionFromValue(0,
                                                     MAX_PERCENT,
                                                     handlePos,
                                                     sliderBarWidth);

    // Handle drawing rectangle is shifted according to position on handle bar:
    // - on left adge handle rectangle is placed between min and handle width.
    // - on right adge handle rectangle is placed between max - handle width and max.
    // - on center handle rectangle is placed between center - handle width / 2 and center + handle width / 2.
    const double shiftRatio {static_cast<double>(handlePos) / MAX_PERCENT};
    return mousePosX <= handlePosX + handleRect_.width() * (1 - shiftRatio) &&
           mousePosX >= handlePosX - handleRect_.width() * shiftRatio;
}

void DoubleSlider::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) == 0U)
    {
        moving_ = Handle::NONE;
        return;
    }

    const int newPosition = getMousePosition(event);
    const int minX = getHandlePosition(Handle::LEFT);
    const int maxX = getHandlePosition(Handle::RIGHT);

    const bool onMinHandle = mouseIsOnHandle(event->x(), minX);
    const bool onMaxHandle = mouseIsOnHandle(event->x(), maxX);

    const double range {max_ - min_};
    const double newCurrent =
        static_cast<double>(newPosition) / MAX_PERCENT * range + min_;

    if (moving_ == Handle::LEFT || (moving_ == Handle::NONE && onMinHandle))
    {
        setCurrentMin(newCurrent);
        moving_ = Handle::LEFT;
    }

    if (moving_ == Handle::RIGHT || (moving_ == Handle::NONE && onMaxHandle))
    {
        setCurrentMax(newCurrent);
        moving_ = Handle::RIGHT;
    }
}

int DoubleSlider::getHandlePosition(Handle handle) const
{
    const double range {max_ - min_};
    const double currentValue =
        (handle == Handle::LEFT ? currentMin_ : currentMax_) - min_;
    return static_cast<int>((std::round(currentValue / range * MAX_PERCENT)));
}

void DoubleSlider::drawSliderBar(QPainter& painter) const
{
    QStyleOptionSlider barStyle;
    initStyleOption(&barStyle);
    const QRect innerRect(barStyle.rect);

    const int handleHight =
        static_cast<int>(innerRect.height() * BAR_HEIGHT_RATIO);
    const QRect plain = QRect(innerRect.x() + handleRect_.width() / 4,
                              innerRect.y() + handleHight,
                              innerRect.width() - handleRect_.width() / 2,
                              handleHight);
    qDrawPlainRect(&painter, plain, palette().color(QPalette::Dark));
}

int DoubleSlider::getHandleMiddlePosX(int handlePos, int handleWidth, int span) const
{
    const int handlePosX =
        QStyle::sliderPositionFromValue(0, MAX_PERCENT, handlePos, span);
    const double handleShiftRatio {handlePos / static_cast<double>(MAX_PERCENT)};
    const int handleMiddleX =
        handlePosX + static_cast<int>(std::round((1 - handleShiftRatio) * handleWidth / 2.));
    return handleMiddleX;
}

void DoubleSlider::setHandleRect()
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    handleRect_ = style()->subControlRect(QStyle::CC_Slider,
                                          &defaultStyle,
                                          QStyle::SC_SliderHandle,
                                          this);
}

void DoubleSlider::drawSliderBarBetweenHandles(QPainter& painter) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);

    const int barHeight =
        static_cast<int>(std::round(innerRect.height() * BAR_HEIGHT_RATIO));

    const int leftHandlePosition = getHandlePosition(Handle::LEFT);
    const int rightHandlePosition = getHandlePosition(Handle::RIGHT);

    const int leftHandleMiddleX =
        getHandleMiddlePosX(leftHandlePosition,
                            handleRect_.width(),
                            innerRect.width() - innerRect.x());

    const int rightHandleMiddleX =
        getHandleMiddlePosX(rightHandlePosition,
                            handleRect_.width(),
                            innerRect.width() - innerRect.x());

    const QRect barRect = QRect(innerRect.x() + leftHandleMiddleX,
                                innerRect.y() + barHeight,
                                innerRect.x() + rightHandleMiddleX - leftHandleMiddleX,
                                barHeight);

    const QBrush brush = palette().brush(QPalette::Dark);
    qDrawShadePanel(&painter, barRect, palette(), true, 1, &brush);
}

QStyleOptionSlider DoubleSlider::getHandleStyle(bool moving, int position) const
{
    QStyleOptionSlider handleStyle;
    initStyleOption(&handleStyle);
    handleStyle.sliderPosition = position;
    if (moving)
    {
        handleStyle.state = QStyle::State_Raised;
    }
    handleStyle.subControls = QStyle::SC_SliderHandle;
    return handleStyle;
}

void DoubleSlider::drawHandles(QPainter& painter) const
{
    const QStyleOptionSlider leftStyle =
        getHandleStyle(moving_ == Handle::LEFT, getHandlePosition(Handle::LEFT));
    style()->drawComplexControl(QStyle::CC_Slider, &leftStyle, &painter, this);

    const QStyleOptionSlider rightStyle =
        getHandleStyle(moving_ == Handle::RIGHT, getHandlePosition(Handle::RIGHT));
    style()->drawComplexControl(QStyle::CC_Slider, &rightStyle, &painter, this);
}

void DoubleSlider::paintEvent(QPaintEvent* event)
{
    if (doublesAreEqual(min_, max_))
    {
        return;
    }

    QPainter painter(this);
    painter.setClipRegion(event->region());

    drawSliderBar(painter);
    drawSliderBarBetweenHandles(painter);
    drawHandles(painter);
}
