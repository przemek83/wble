#pragma once

#include <QLabel>
#include <QWidget>

#include <wble/DoubleSlider.h>
#include <wble/FilterDates.h>
#include <wble/FilterDoubles.h>
#include <wble/FilterIntegers.h>
#include <wble/FilterStrings.h>

class QVBoxLayout;
class QGroupBox;
class ProgressBar;
class QPushButton;

class Examples : public QWidget
{
public:
    Examples();

private:
    DoubleSlider* getDoubleSlider();
    FilterNumbers* createFilterIntegers();
    FilterNumbers* createFilterDoubles();
    FilterDates* createFilterDates();
    FilterStrings* createFilterStrings();
    QVBoxLayout* createLeftWidgetColumn();
    QGroupBox* wrapProgressBar(const QString& name, ProgressBar* progressBar,
                               QPushButton* startStopButton);
    QGroupBox* createProgressBarInfinite();
    QGroupBox* createProgressBarCounter();
    QVBoxLayout* createRightWidgetColumn();

    static constexpr double MIN{3};
    static constexpr double MAX{56};

    static constexpr int MAX_PROGRESS_BAR_VALUE{100};

    static constexpr int DEFAULT_SPACING{10};

    QLabel info_;

    DoubleSlider doubleSlider_;
    FilterIntegers filterIntegers_;
    FilterDoubles filterDoubles_;
    FilterDates filterDates_;
    FilterStrings filterStrings_;

private slots:
    void doubleSliderMinChanged(double min);
    void doubleSliderMaxChanged(double max);
};
