#ifndef PROGRESSBARINFINITE_H
#define PROGRESSBARINFINITE_H

#include "ProgressBar.h"

class WBLE_EXPORT ProgressBarInfinite : public ProgressBar
{
public:
    ProgressBarInfinite(QString title, QWidget* parent = nullptr);

    void start() override;

    void stop() override;

protected:
    void paintProgress(QPainter& painter) override;

    void timerEvent(QTimerEvent* event) override;

private:
    int timerId_ {0};

    static constexpr int TIMER_DEFAULT_INTERVAL {40};

    unsigned int progressCounter_ {0};
};

#endif // PROGRESSBARINFINITE_H
