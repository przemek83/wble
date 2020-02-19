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

    void changeEvent(QEvent* event) override;

private:
    enum class Handle : unsigned short int
    {
        NONE,
        LEFT,
        RIGHT
    };

    int getLeftHandlePosition() const;

    int getRightHandlePosition() const;

    void drawSliderBar(QPainter& painter) const;

    void drawSliderBarBetweenHandles(QPainter& painter) const;

    QStyleOptionSlider getHandleStyle(bool moving, int position) const;

    void drawHandles(QPainter& painter) const;

    int getMousePosition(QMouseEvent* event) const;

    bool mouseIsOnHandle(int mousePosX, int handlePos) const;

    int getHandleMiddlePosX(int handlePos, int handleWidth, int span) const;

    void setHandleRect();

    double currentMin_ {0.};

    double currentMax_ {0.};

    const double minValue_;

    const double maxValue_;

    double lastEmittedMin_ {0.};

    double lastEmittedMax_ {0.};

    static constexpr int MAX_PERCENT{100};

    static constexpr double BAR_HEIGHT_RATIO{1. / 3.};

    QRect handleRect_;

    ///Flag to remember handle is moving.
    Handle moving_{Handle::NONE};

Q_SIGNALS:
    void minChanged(double);

    void maxChanged(double);
};

#endif // DOUBLESLIDER_H
