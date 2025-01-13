#pragma once

#include "ProgressBar.h"

/// @class ProgressBarCounter
/// @brief Round progress bar with percent counter.
class WBLE_EXPORT ProgressBarCounter : public ProgressBar
{
    Q_OBJECT
public:
    /// Constructor of ProgressBarCounter class.
    /// @param title Title to be shown.
    /// @param maxValue Maximum value after hitting which 100% is achieved..
    /// @param parent Parent widget.
    ProgressBarCounter(QString title, int maxValue, QWidget* parent);
    ProgressBarCounter(QString title, int maxValue);

    void reset() override;

public Q_SLOTS:
    /// Update progress with new value.
    /// @param newValue New value for drawing progress: % = newValue/maxValue_.
    void updateProgress(int newValue);

protected:
    void paintProgressBar(QPainter& painter) override;

private:
    int currentPercent_{0};

    const int maxValue_;
};
