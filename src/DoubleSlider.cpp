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
    QSlider(parent), minValue_(min), maxValue_(max)
{
    setOrientation(Qt::Horizontal);

    setCurrentMin(minValue_);
    setCurrentMax(maxValue_);

    lastEmittedMin_ = getCurrentMin();
    lastEmittedMax_ = getCurrentMax();

    setMouseTracking(true);

    setMinimum(0);
    setMaximum(100);
}

double DoubleSlider::getCurrentMin()
{
    return currentMin_ + minValue_;
}

double DoubleSlider::getCurrentMax()
{
    return currentMax_ + minValue_;
}

void DoubleSlider::setCurrentMin(double currentMinToSet)
{
    if (currentMinToSet >= minValue_ && !doublesAreEqual(currentMin_, currentMinToSet))
    {
        currentMin_ = currentMinToSet;
        if (!doublesAreEqual(lastEmittedMin_, currentMinToSet))
        {
            lastEmittedMin_ = currentMinToSet;
            Q_EMIT minChanged(currentMinToSet);
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
    if (currentMaxToSet <= maxValue_ && !doublesAreEqual(currentMax_, currentMaxToSet))
    {
        currentMax_ = currentMaxToSet;
        if (!doublesAreEqual(lastEmittedMax_, currentMaxToSet))
        {
            lastEmittedMax_ = currentMaxToSet;
            Q_EMIT maxChanged(currentMaxToSet);
        }
    }

    if (currentMaxToSet < currentMin_)
    {
        setCurrentMin(currentMaxToSet);
    }

    update();
}

int DoubleSlider::getMousePosX(QMouseEvent* event) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);
    int pos = QStyle::sliderValueFromPosition(0, MAX_PERCENT, event->x(), innerRect.width() - innerRect.x());
    return pos;
}

void DoubleSlider::mousePressEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) != 0U)
    {
        mousePositionX_ = getMousePosX(event);
    }

    moving_ = 0;
}

void DoubleSlider::mouseReleaseEvent(QMouseEvent* event)
{
    moving_ = 0;
    mouseMoveEvent(event);
    update();
}

bool DoubleSlider::mouseIsOnHandle(int mousePosX, int handlePos) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);
    int handlePosX = QStyle::sliderPositionFromValue(0, MAX_PERCENT, handlePos, innerRect.width() - innerRect.x());

    const QRect handleRect = style()->subControlRect(QStyle::CC_Slider,
                                                     &defaultStyle,
                                                     QStyle::SC_SliderHandle,
                                                     this);

    // Handle drawing rectangle is shifted according to position on handle bar:
    // - on left adge handle rectangle is placed between min and handle width.
    // - on right adge handle rectangle is placed between max - handle width and max.
    // - on center handle rectangle is placed between center - handle width / 2 and center + handle width / 2.
    const double shiftRatio {handlePos / static_cast<double>(MAX_PERCENT)};
    return mousePosX <= handlePosX + handleRect.width() * (1 - shiftRatio) &&
           mousePosX >= handlePosX - handleRect.width() * shiftRatio;
}

void DoubleSlider::mouseMoveEvent(QMouseEvent* event)
{
    double mouseX = getMousePosX(event);
    double minX = getLeftHandlePosition();
    double maxX = getRightHandlePosition();

    bool onMinHandle = mouseIsOnHandle(event->x(), minX);
    bool onMaxHandle = mouseIsOnHandle(event->x(), maxX);

    //qDebug() << "On min" << onMinHandle << "on max" << onMaxHandle;

    isOnMinHandle_ = onMinHandle && moving_ != 2 && !isOnMaxHandle_;
    isOnMaxHandle_ = onMaxHandle && moving_ != 1 && !isOnMinHandle_;

    if ((event->buttons() & Qt::LeftButton) != 0U)
    {
        if ((moving_ != 2) && isOnMinHandle_)
        {
            minX += mouseX - mousePositionX_;
            if (minX < 0)
            {
                minX = 0;
            }
            if (minX > MAX_PERCENT)
            {
                minX = MAX_PERCENT;
            }
            setCurrentMin(minX / MAX_PERCENT * (maxValue_ - minValue_) + minValue_);

            if (currentMax_ < currentMin_)
            {
                setCurrentMax(minX);
            }

            moving_ = 1;
        }

        if ((moving_ != 1) && isOnMaxHandle_)
        {
            maxX += mouseX - mousePositionX_;
            if (maxX < 0)
            {
                maxX = 0;
            }
            if (maxX > MAX_PERCENT)
            {
                maxX = MAX_PERCENT;
            }
            setCurrentMax(maxX / MAX_PERCENT * (maxValue_ - minValue_) + minValue_);
            if (currentMin_ > currentMax_)
            {
                setCurrentMin(maxX);
            }

            moving_ = 2;
        }
    }
    else
    {
        moving_ = 0;
    }

    mousePositionX_ = mouseX;
}

int DoubleSlider::getLeftHandlePosition() const
{
    const double range {maxValue_ - minValue_};
    const int minX =
        static_cast<int>((std::round((currentMin_ - minValue_) / range * MAX_PERCENT)));
    return minX;
}

int DoubleSlider::getRightHandlePosition() const
{
    const double range {maxValue_ - minValue_};
    const int maxX =
        static_cast<int>(std::round((currentMax_ - minValue_) / range * MAX_PERCENT));
    return maxX;
}

void DoubleSlider::drawSliderBar(QPainter& painter) const
{
    QStyleOptionSlider barStyle;
    initStyleOption(&barStyle);
    const QRect innerRect(barStyle.rect);
    const QRect handleRect = style()->subControlRect(QStyle::CC_Slider,
                                                     &barStyle,
                                                     QStyle::SC_SliderHandle,
                                                     this);
    const int handleHight =
        static_cast<int>(innerRect.height() * BAR_HEIGHT_RATIO);
    const QRect plain = QRect(innerRect.x() + handleRect.width() / 4,
                              innerRect.y() + handleHight,
                              innerRect.width() - handleRect.width() / 2,
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

void DoubleSlider::drawSliderBarBetweenHandles(QPainter& painter) const
{
    QStyleOptionSlider defaultStyle;
    initStyleOption(&defaultStyle);
    const QRect innerRect(defaultStyle.rect);

    const int barHeight =
        static_cast<int>(std::round(innerRect.height() * BAR_HEIGHT_RATIO));
    const QRect handleRect = style()->subControlRect(QStyle::CC_Slider,
                                                     &defaultStyle,
                                                     QStyle::SC_SliderHandle,
                                                     this);

    const int leftHandlePosition = getLeftHandlePosition();
    const int rightHandlePosition = getRightHandlePosition();

    const int leftHandleMiddleX =
        getHandleMiddlePosX(leftHandlePosition,
                            handleRect.width(),
                            innerRect.width() - innerRect.x());

    const int rightHandleMiddleX =
        getHandleMiddlePosX(rightHandlePosition,
                            handleRect.width(),
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
        getHandleStyle(moving_ == 1, getLeftHandlePosition());
    style()->drawComplexControl(QStyle::CC_Slider, &leftStyle, &painter, this);

    const QStyleOptionSlider rightStyle =
        getHandleStyle(moving_ == 2, getRightHandlePosition());
    style()->drawComplexControl(QStyle::CC_Slider, &rightStyle, &painter, this);
}

void DoubleSlider::paintEvent(QPaintEvent* event)
{
    if (doublesAreEqual(minValue_, maxValue_))
    {
        return;
    }

    QPainter painter(this);
    painter.setClipRegion(event->region());

    drawSliderBar(painter);
    drawSliderBarBetweenHandles(painter);
    drawHandles(painter);
}
