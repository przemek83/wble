#pragma once

#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include <wble/DoubleSlider.h>
#include <wble/FilterDates.h>
#include <wble/FilterDoubles.h>
#include <wble/FilterIntegers.h>
#include <wble/FilterStrings.h>
#include <wble/ProgressBarCounter.h>
#include <wble/ProgressBarInfinite.h>

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
    FilterNumbers* getFilterIntegers();
    FilterNumbers* getFilterDoubles();
    FilterDates* getFilterDates();
    FilterStrings* getFilterStrings();
    QVBoxLayout* createLeftWidgetColumn();
    static QGroupBox* wrapProgressBar(const QString& name,
                                      ProgressBar* progressBar,
                                      QPushButton* startStopButton);
    QGroupBox* createProgressBarInfinite();
    QGroupBox* createProgressBarCounter();
    QVBoxLayout* createRightWidgetColumn();

    static constexpr double MIN{3};
    static constexpr double MAX{56};

    static constexpr int MAX_PROGRESS_BAR_VALUE{100};

    static constexpr int DEFAULT_SPACING{10};

    static constexpr int TIME_INTERVAL{40};

    QLabel info_;

    int progress_{0};

    const QDate startDate_{2010, 9, 21};
    const QDate endDate_{2012, 2, 25};

    const QStringList exampleStringsList_{
        QStringLiteral("a"), QStringLiteral("b"), QStringLiteral("c"),
        QStringLiteral("d")};

    DoubleSlider doubleSlider_;
    FilterIntegers filterIntegers_;
    FilterDoubles filterDoubles_;
    FilterDates filterDates_;
    FilterStrings filterStrings_;
    ProgressBarInfinite progressBarInfinite_;
    ProgressBarCounter progressBarCounter_;
    QPushButton startStopButtonInfinite_;
    QPushButton startStopButtonCounter_;
    QTimer progressCounterTimer_;

private slots:
    void doubleSliderMinChanged(double min);
    void doubleSliderMaxChanged(double max);

    void filterIntegersValuesChanged(int min, int max);

    void filterDoublesValuesChanged(double min, double max);

    void filterDatesValuesChanged(QDate from, QDate to, bool filterEmptyDates);

    void filterStringsValuesChanged(QStringList bannedItems);

    void infiniteButtonClicked();

    void counterButtonClicked();

    void counterTimerEvent();
};
