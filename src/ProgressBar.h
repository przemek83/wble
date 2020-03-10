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

protected:
    void paintEvent(QPaintEvent* event) override;

    void initPainter(QPainter* painter) const override;

    static constexpr int FULL_DEGREE {16};
    static constexpr double HUNDREDTH_OF_FULL_CIRCLE {3.6};
    static constexpr int QUARTER_CIRCLE_ANGLE {90};
    static constexpr int HALF_CIRCLE_ANGLE {2 * QUARTER_CIRCLE_ANGLE};

    virtual void paintProgress(QPainter& painter) = 0;

    ///Area of round display.
    QRect arcRectangle_;

private:
    void paintTitle(QPainter& painter);

    const QString title_;

    ///Font used to display %.
    QFont counterFont_;

    ///Font used do draw title.
    QFont titleFont_;

    ///Title area.
    QRect titleRectangle_;

    QPen pen_;

    QBrush brush_;

    static constexpr int LINE_WIDTH {10};

    bool running_ {false};
};

#endif // PROGRESSBAR_H
