#ifndef PROGRESSBARCOUNTER_H
#define PROGRESSBARCOUNTER_H

#include "ProgressBar.h"

class WBLE_EXPORT ProgressBarCounter : public ProgressBar
{
public:
    ProgressBarCounter(QString title, int maxValue, QWidget* parent = nullptr);

    int getCurrentPercent();

    void stop() override;

public Q_SLOTS:
    void updateProgress(int newValue);

protected:
    void paintProgress(QPainter& painter) override;

private:
    int currentPercent_ {0};

    const int maxValue_;
};

#endif // PROGRESSBARCOUNTER_H
