#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QPen>
#include <QApplication>
#include <cmath>

#include "wble_global.h"

/**
 * @brief Round progress bar to show progress. If max != 0 '%' are used.
 */
class WBLE_EXPORT ProgressBar : public QWidget
{
    Q_OBJECT
public:
    ProgressBar(QString title, int max, QWidget* parent = nullptr);

    ~ProgressBar() override = default;

    ProgressBar& operator=(const ProgressBar& other) = delete;
    ProgressBar(const ProgressBar& other) = delete;

    ProgressBar& operator=(ProgressBar&& other) = delete;
    ProgressBar(ProgressBar&& other) = delete;

    void start();

    void stop();

    void restart();

    int getCurrentPercent();

    bool isRunning();

public Q_SLOTS:
    void updateProgress(int newValue);

protected:
    void paintEvent(QPaintEvent* event) override;

    void timerEvent(QTimerEvent* event) override;

private:
    int timerId_ {0};

    bool running_ {false};

    int currentPercent_ {0};

    const int maxValue_;

    const QString title_;

    ///Font used to display %.
    QFont counterFont_;

    ///Font used do draw title.
    QFont titleFont_;

    ///Area of round display.
    QRect arcRectangle_;

    ///Title area.
    QRect titleRectangle_;

    QPen pen_;

    QBrush brush_;

    static constexpr int LINE_WIDTH {10};

    static constexpr int TIMER_DEFAULT_INTERVAL {40};
};

#endif // PROGRESSBAR_H
