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
 * @class ProgressBar
 * @brief Round progress bar to visualize task progress.
 */
class WBLE_EXPORT ProgressBar : public QWidget
{
    Q_OBJECT
public:
    /**
     * Constructor of ProgressBar class.
     * @param title Title to be shown.
     * @param parent Parent widget.
     */
    explicit ProgressBar(QString title, QWidget* parent = nullptr);

    ~ProgressBar() override = default;

    ProgressBar& operator=(const ProgressBar& other) = delete;
    ProgressBar(const ProgressBar& other) = delete;

    ProgressBar& operator=(ProgressBar&& other) = delete;
    ProgressBar(ProgressBar&& other) = delete;

    virtual void start();

    virtual void stop();

    virtual void reset();

    bool isRunning();

    /// Without parent, draw progress bar as seperate frameless window.
    void showDetached();

protected:
    void paintEvent(QPaintEvent* event) override;

    void initPainter(QPainter* painter) const override;

    static constexpr int FULL_DEGREE {16};
    static constexpr double HUNDREDTH_OF_FULL_CIRCLE {3.6};
    static constexpr int QUARTER_CIRCLE_ANGLE {90};
    static constexpr int HALF_CIRCLE_ANGLE {2 * QUARTER_CIRCLE_ANGLE};

    /**
     * Paint graphically progress bar arc.
     * @param painter Painter which should be used.
     */
    virtual void paintProgressBar(QPainter& painter) = 0;

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

    /// Font used to display percent.
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
