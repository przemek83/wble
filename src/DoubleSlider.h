#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QSlider>

#include "wble_global.h"

/**
 * @brief Slider with 2 handles.
 */
class WBLE_EXPORT DoubleSlider : public QSlider
{
    Q_OBJECT
public:
    DoubleSlider(double min, double max, QWidget* parent = nullptr);

    ~DoubleSlider() override = default;

    DoubleSlider& operator=(const DoubleSlider& other) = delete;
    DoubleSlider(const DoubleSlider& other) = delete;

    DoubleSlider& operator=(DoubleSlider&& other) = delete;
    DoubleSlider(DoubleSlider&& other) = delete;

public Q_SLOTS:
    void setCurrentMin(double currentMinToSet);

    void setCurrentMax(double currentMaxToSet);

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

private:
    double getCurrentMin();

    double getCurrentMax();

    int getLeftHandlePosition() const;

    int getRightHandlePosition() const;

    void drawSliderBar(QPainter& painter) const;

    void drawSliderBarBetweenHandles(QPainter& painter) const;

    QStyleOptionSlider getHandleStyle(bool moving, int position) const;

    void drawHandles(QPainter& painter) const;

    int getMousePosX(QMouseEvent* event) const;

    bool mouseIsOnHandle(int mousePosX, int handlePos) const;

    int getHandleMiddlePosX(int handlePos, int handleWidth, int span) const;

    double currentMin_ {0.};

    double currentMax_ {0.};

    double minValue_;

    double maxValue_;

    static constexpr int cursorSize_{16};

    double mousePositionX_{0.};

    double lastEmittedMin_ {0.};

    double lastEmittedMax_ {0.};

    ///Flag to remember handle is moving.
    int moving_{0};

    ///Mouse on left handle.
    bool isOnMinHandle_{false};

    ///Mouse on right handle.
    bool isOnMaxHandle_{false};

    static constexpr int MAX_PERCENT{100};

    static constexpr double BAR_HEIGHT_RATIO{1. / 3.};

Q_SIGNALS:
    void minChanged(double);

    void maxChanged(double);
};

#endif // DOUBLESLIDER_H
