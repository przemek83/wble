#ifndef PROGRESSBARINFINITE_H
#define PROGRESSBARINFINITE_H

#include "ProgressBar.h"

/**
 * @class ProgressBarInfinite
 * @brief Round progress showing two arcs moving infinitely.
 */
class WBLE_EXPORT ProgressBarInfinite : public ProgressBar
{
    Q_OBJECT
public:
    /**
     * Constructor of ProgressBarCounter class.
     * @param title Title to be shown.
     * @param parent Parent widget.
     */
    ProgressBarInfinite(QString title, QWidget* parent = nullptr);

    void start() override;

    void stop() override;

    void reset() override;

protected:
    void paintProgressBar(QPainter& painter) override;

    void timerEvent(QTimerEvent* event) override;

private:
    int timerId_ {0};

    static constexpr int TIMER_DEFAULT_INTERVAL {40};

    unsigned int progressCounter_ {0};
};

#endif // PROGRESSBARINFINITE_H
