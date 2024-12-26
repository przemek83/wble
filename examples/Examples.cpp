#include "Examples.h"

#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QTimer>
#include <QVBoxLayout>
#include <QWindow>

#include <wble/DoubleSlider.h>
#include <wble/FilterDates.h>
#include <wble/FilterDoubles.h>
#include <wble/FilterIntegers.h>
#include <wble/FilterStrings.h>
#include <wble/ProgressBarCounter.h>
#include <wble/ProgressBarInfinite.h>

Examples::Examples() : info_(QStringLiteral("Status"))
{
    setWindowTitle("Wble library examples");
    QHBoxLayout* widgetLayout = new QHBoxLayout(this);
    QVBoxLayout* leftWidgetColumn = createLeftWidgetColumn();
    widgetLayout->addLayout(leftWidgetColumn);
    QVBoxLayout* rightWidgetColumn = createRightWidgetColumn();
    widgetLayout->addLayout(rightWidgetColumn);
    setLayout(widgetLayout);
}

DoubleSlider* Examples::createDoubleSlider()
{
    auto* slider = new DoubleSlider(MIN, MAX);
    QObject::connect(
        slider, &DoubleSlider::currentMinChanged, &info_,
        [&info = info_](double min)
        { info.setText("Double Slider: min = " + QString::number(min)); });

    QObject::connect(
        slider, &DoubleSlider::currentMaxChanged, &info_,
        [&info = info_](double max)
        { info.setText("Double Slider: max = " + QString::number(max)); });

    return slider;
}

FilterNumbers* Examples::createFilterIntegers()
{
    auto* filterNumbers =
        new FilterIntegers(QStringLiteral("Integers Filter"), MIN, MAX);
    QObject::connect(
        filterNumbers, &FilterIntegers::newNumericFilter, &info_,
        [&info = info_](int min, int max)
        {
            info.setText("Integers Filter: " + QString::number(min) + " | " +
                         QString::number(max));
        });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

FilterNumbers* Examples::createFilterDoubles()
{
    auto* filterNumbers =
        new FilterDoubles(QStringLiteral("Doubles Filter"), MIN, MAX);
    QObject::connect(
        filterNumbers, &FilterDoubles::newNumericFilter, &info_,
        [&info = info_](double min, double max)
        {
            info.setText("Doubles Filter: " + QString::number(min) + " | " +
                         QString::number(max));
        });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

FilterDates* Examples::createFilterDates()
{
    auto* filterDates =
        new FilterDates(QStringLiteral("Dates Filter"), QDate(2010, 9, 21),
                        QDate(2012, 2, 25), true);
    QObject::connect(
        filterDates, &FilterDates::newDateFilter, &info_,
        [&info = info_](QDate from, QDate to, bool filterEmptyDates)
        {
            info.setText("Dates Filter: " + from.toString() + " | " +
                         to.toString() + " | " +
                         (filterEmptyDates ? "yes" : "no"));
        });

    filterDates->setCheckable(true);
    return filterDates;
}

FilterStrings* Examples::createFilterStrings()
{
    auto* filterNames = new FilterStrings(
        QStringLiteral("Names Filter"),
        QStringList{QStringLiteral("a"), QStringLiteral("b"),
                    QStringLiteral("c"), QStringLiteral("d")});
    QObject::connect(filterNames, &FilterStrings::newStringFilter, &info_,
                     [&info = info_](const QStringList& bannedItems) {
                         info.setText("Names Filter: " + bannedItems.join(','));
                     });

    filterNames->setCheckable(true);
    return filterNames;
}

QVBoxLayout* Examples::createLeftWidgetColumn()
{
    auto* leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(DEFAULT_SPACING);
    auto* groupBox = new QGroupBox(QStringLiteral("Double Slider"));
    auto* layout = new QVBoxLayout(groupBox);
    layout->addWidget(createDoubleSlider());
    groupBox->setLayout(layout);
    leftLayout->addWidget(groupBox);
    leftLayout->addWidget(createFilterIntegers());
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
    auto* groupBox = new QGroupBox(name);
    auto* layout = new QVBoxLayout();
    layout->addWidget(progressBar);
    layout->addWidget(startStopButton);
    groupBox->setLayout(layout);
    return groupBox;
}

QGroupBox* Examples::createProgressBarInfinite()
{
    auto* progressBar = new ProgressBarInfinite(QStringLiteral("Title"));
    auto* startStopButton = new QPushButton(QStringLiteral("start"));
    QObject::connect(
        startStopButton, &QPushButton::clicked, progressBar,
        [=]()
        {
            const bool running = progressBar->isRunning();
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
    auto* progressBar =
        new ProgressBarCounter(QStringLiteral("Title"), MAX_PROGRESS_BAR_VALUE);
    auto* startStopButton = new QPushButton(QStringLiteral("start"));
    auto* timer = new QTimer(progressBar);
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
    auto* rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(DEFAULT_SPACING);
    rightLayout->addWidget(createProgressBarInfinite());
    rightLayout->addWidget(createProgressBarCounter());
    rightLayout->addStretch();
    return rightLayout;
}
