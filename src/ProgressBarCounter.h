#ifndef PROGRESSBARCOUNTER_H
#define PROGRESSBARCOUNTER_H

#include "ProgressBar.h"

class WBLE_EXPORT ProgressBarCounter : public ProgressBar
{
public:
    /**
     * Constructor of ProgressBarCounter class.
     * @param title Title to be shown.
     * @param maxValue Maximum value after hitting which 100% is achieved..
     * @param parent Parent widget.
     */
    ProgressBarCounter(QString title, int maxValue, QWidget* parent = nullptr);

    void stop() override;

public Q_SLOTS:
    void updateProgress(int newValue);

protected:
    void paintProgressBar(QPainter& painter) override;

private:
    int currentPercent_ {0};

    const int maxValue_;
};

#endif // PROGRESSBARCOUNTER_H
