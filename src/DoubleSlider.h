#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QSlider>

#include "wble_global.h"

/**
 * @class DoubleSlider
 * @brief Slider with two moving independently handles.
 */
class WBLE_EXPORT DoubleSlider : public QSlider
{
    Q_OBJECT
public:
    /**
     * Constructor of DoubleSlider class.
     * @param min Minimum value of slider.
     * @param max Maximum value of slider.
     * @param parent Parent widget.
     */
    DoubleSlider(double min, double max, QWidget* parent = nullptr);

    ~DoubleSlider() override = default;

    /**
     * Get slider minimum value.
     * @return Slider minimum value.
     */
    double getMin() const;

    /**
     * Get slider maximum value.
     * @return Slider maximum value.
     */
    double getMax() const;

    /**
     * Get current value of left handle (minimum).
     * @return Current minimum value.
     */
    double getCurrentMin() const;

    /**
     * Get current value of right handle (maximum).
     * @return Current maximum value.
     */
    double getCurrentMax() const;

public Q_SLOTS:
    /**
     * Set current minimum.
     * @param currentMinToSet Minimum value to set.
     */
    void setCurrentMin(double currentMinToSet);

    /**
     * Set current maximum.
     * @param currentMaxToSet Maximum value to set.
     */
    void setCurrentMax(double currentMaxToSet);

Q_SIGNALS:
    /**
     * Signal emitted when minimum value has changed (left slider moved).
     */
    void currentMinChanged(double currentMin);

    /**
     * Signal emitted when maximum value has changed (right slider moved).
     */
    void currentMaxChanged(double currentMax);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void changeEvent(QEvent* event) override;

private:
    enum class Handle : unsigned short int
    {
        NONE,
        LEFT,
        RIGHT
    };

    int getHandlePosition(Handle handle) const;

    void drawSliderBar(QPainter& painter) const;

    void drawSliderBarBetweenHandles(QPainter& painter) const;

    QStyleOptionSlider getHandleStyle(bool moving, int position) const;

    void drawHandles(QPainter& painter) const;

    int getMousePosition(QMouseEvent* event) const;

    bool mouseIsOnHandle(int mousePosX, int handlePos) const;

    int getHandleMiddlePosX(int handlePos, int handleWidth, int span) const;

    void setHandleRect();

    double getNormalizedValue(double value);

    const double min_;
    const double max_;

    double currentMin_{0.};
    double currentMax_{0.};

    double lastEmittedMin_{0.};
    double lastEmittedMax_{0.};

    static constexpr int MAX_PERCENT{100};

    static constexpr double BAR_HEIGHT_RATIO{1. / 3.};

    QRect handleRect_;

    /// Flag to remember which handle is moving.
    Handle moving_{Handle::NONE};
};

#endif  // DOUBLESLIDER_H
