#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <cmath>
#include <memory>

#include <QApplication>
#include <QPainter>
#include <QPen>
#include <QWidget>

#include "wble_global.h"

/**
 * @brief Round progress bar to show progress. If max != 0 '%' are used.
 */
class WBLE_EXPORT ProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBar(QString title, QWidget* parent = nullptr);

    ~ProgressBar() override = default;

    ProgressBar& operator=(const ProgressBar& other) = delete;
    ProgressBar(const ProgressBar& other) = delete;

    ProgressBar& operator=(ProgressBar&& other) = delete;
    ProgressBar(ProgressBar&& other) = delete;

    virtual void start();

    virtual void stop();

    void restart();

    bool isRunning();

    void showDetached();

protected:
    void paintEvent(QPaintEvent* event) override;

    void initPainter(QPainter* painter) const override;

    static constexpr int FULL_DEGREE {16};
    static constexpr double HUNDREDTH_OF_FULL_CIRCLE {3.6};
    static constexpr int QUARTER_CIRCLE_ANGLE {90};
    static constexpr int HALF_CIRCLE_ANGLE {2 * QUARTER_CIRCLE_ANGLE};

    virtual void paintProgress(QPainter& painter) = 0;

    /// Area of round display.
    QRect arcRectangle_;

private:
    void initSizes();
    void initPen();
    void initCounterFont();
    void initTitleFont();
    void initArcRectangle();
    void initTitleRectangle();

    void paintTitle(QPainter& painter);

    const QString title_;

    /// Font used to display %.
    QFont counterFont_;

    /// Font used do draw title.
    QFont titleFont_;

    /// Title area.
    QRect titleRectangle_;

    QPen pen_;

    const QColor color_;

    const QBrush brush_;

    static constexpr int LINE_WIDTH {10};
    static constexpr int TITLE_HEIGHT {LINE_WIDTH * 3};
    static constexpr int DEFAULT_WIDTH {120};
    static constexpr int DEFAULT_HEIGHT {140};
    static constexpr double COUNTER_FONT_FACTOR {2.5};
    static constexpr double TITLE_FONT_FACTOR {1.5};

    bool running_ {false};
};

#endif // PROGRESSBAR_H
