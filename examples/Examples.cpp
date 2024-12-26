#include "Examples.h"

#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QTimer>
#include <QVBoxLayout>
#include <QWindow>

#include <wble/ProgressBarCounter.h>
#include <wble/ProgressBarInfinite.h>

Examples::Examples()
    : info_(QStringLiteral("Status")),
      doubleSlider_{MIN, MAX},
      filterIntegers_{QStringLiteral("Integers Filter"), MIN, MAX},
      filterDoubles_{QStringLiteral("Doubles Filter"), MIN, MAX},
      filterDates_{QStringLiteral("Dates Filter"), startDate_, endDate_, true},
      filterStrings_{QStringLiteral("Names Filter"), exampleStringsList_}
{
    setWindowTitle("Wble library examples");
    QHBoxLayout* widgetLayout{new QHBoxLayout(this)};
    QVBoxLayout* leftWidgetColumn = createLeftWidgetColumn();
    widgetLayout->addLayout(leftWidgetColumn);
    QVBoxLayout* rightWidgetColumn = createRightWidgetColumn();
    widgetLayout->addLayout(rightWidgetColumn);
    setLayout(widgetLayout);
}

DoubleSlider* Examples::getDoubleSlider()
{
    QObject::connect(&doubleSlider_, &DoubleSlider::currentMinChanged, this,
                     &Examples::doubleSliderMinChanged);

    QObject::connect(&doubleSlider_, &DoubleSlider::currentMaxChanged, this,
                     &Examples::doubleSliderMaxChanged);

    return &doubleSlider_;
}

FilterNumbers* Examples::getFilterIntegers()
{
    QObject::connect(&filterIntegers_, &FilterIntegers::newNumericFilter, this,
                     &Examples::filterIntegersValuesChanged);

    filterIntegers_.setCheckable(true);
    return &filterIntegers_;
}

FilterNumbers* Examples::createFilterDoubles()
{
    QObject::connect(
        &filterDoubles_, &FilterDoubles::newNumericFilter, &info_,
        [&info = info_](double min, double max)
        {
            info.setText("Doubles Filter: " + QString::number(min) + " | " +
                         QString::number(max));
        });

    filterDoubles_.setCheckable(true);
    return &filterDoubles_;
}

FilterDates* Examples::createFilterDates()
{
    QObject::connect(
        &filterDates_, &FilterDates::newDateFilter, &info_,
        [&info = info_](QDate from, QDate to, bool filterEmptyDates)
        {
            info.setText("Dates Filter: " + from.toString() + " | " +
                         to.toString() + " | " +
                         (filterEmptyDates ? "yes" : "no"));
        });

    filterDates_.setCheckable(true);
    return &filterDates_;
}

FilterStrings* Examples::createFilterStrings()
{
    QObject::connect(&filterStrings_, &FilterStrings::newStringFilter, &info_,
                     [&info = info_](const QStringList& bannedItems) {
                         info.setText("Names Filter: " + bannedItems.join(','));
                     });

    filterStrings_.setCheckable(true);
    return &filterStrings_;
}

QVBoxLayout* Examples::createLeftWidgetColumn()
{
    auto* leftLayout{new QVBoxLayout()};
    leftLayout->setSpacing(DEFAULT_SPACING);
    auto* groupBox{new QGroupBox(QStringLiteral("Double Slider"))};
    auto* layout{new QVBoxLayout(groupBox)};
    layout->addWidget(getDoubleSlider());
    groupBox->setLayout(layout);
    leftLayout->addWidget(groupBox);
    leftLayout->addWidget(getFilterIntegers());
    leftLayout->addWidget(createFilterDoubles());
    leftLayout->addWidget(createFilterDates());
    leftLayout->addWidget(createFilterStrings());
    leftLayout->addWidget(&info_);
    leftLayout->addStretch();
    return leftLayout;
}

QGroupBox* Examples::wrapProgressBar(const QString& name,
                                     ProgressBar* progressBar,
                                     QPushButton* startStopButton)
{
    auto* groupBox{new QGroupBox(name)};
    auto* layout{new QVBoxLayout()};
    layout->addWidget(progressBar);
    layout->addWidget(startStopButton);
    groupBox->setLayout(layout);
    return groupBox;
}

QGroupBox* Examples::createProgressBarInfinite()
{
    auto* progressBar{new ProgressBarInfinite(QStringLiteral("Title"))};
    auto* startStopButton{new QPushButton(QStringLiteral("start"))};
    QObject::connect(
        startStopButton, &QPushButton::clicked, progressBar,
        [=]()
        {
            const bool running{progressBar->isRunning()};
            if (running)
                progressBar->stop();
            else
                progressBar->start();
            startStopButton->setText(
                (running ? QStringLiteral("start") : QStringLiteral("stop")));
        });
    return wrapProgressBar(QStringLiteral("Infinite progress bar"), progressBar,
                           startStopButton);
}

QGroupBox* Examples::createProgressBarCounter()
{
    auto* progressBar{new ProgressBarCounter(QStringLiteral("Title"),
                                             MAX_PROGRESS_BAR_VALUE)};
    auto* startStopButton{new QPushButton(QStringLiteral("start"))};
    auto* timer{new QTimer(progressBar)};
    timer->setInterval(40);
    QObject::connect(timer, &QTimer::timeout, progressBar,
                     [=]()
                     {
                         static int progress{0};
                         progressBar->updateProgress(progress);
                         progress++;
                         if (progress > MAX_PROGRESS_BAR_VALUE)
                         {
                             timer->stop();
                             progress = 0;
                             startStopButton->click();
                         }
                     });
    QObject::connect(
        startStopButton, &QPushButton::clicked, progressBar,
        [=]()
        {
            const bool running = progressBar->isRunning();
            if (running)
            {
                progressBar->stop();
                timer->stop();
            }
            else
            {
                progressBar->start();
                timer->start();
            }
            startStopButton->setText(
                (running ? QStringLiteral("start") : QStringLiteral("stop")));
        });
    return wrapProgressBar(QStringLiteral("Counter progress bar"), progressBar,
                           startStopButton);
}

QVBoxLayout* Examples::createRightWidgetColumn()
{
    auto* rightLayout{new QVBoxLayout()};
    rightLayout->setSpacing(DEFAULT_SPACING);
    rightLayout->addWidget(createProgressBarInfinite());
    rightLayout->addWidget(createProgressBarCounter());
    rightLayout->addStretch();
    return rightLayout;
}

void Examples::doubleSliderMinChanged(double min)
{
    info_.setText("Double Slider: min = " + QString::number(min));
}

void Examples::doubleSliderMaxChanged(double max)
{
    info_.setText("Double Slider: max = " + QString::number(max));
}

void Examples::filterIntegersValuesChanged(int min, int max)
{
    info_.setText("Integers Filter: " + QString::number(min) + " | " +
                  QString::number(max));
}
