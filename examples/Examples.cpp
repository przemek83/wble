#include "Examples.h"

#include <QVBoxLayout>

Examples::Examples()
    : info_(QStringLiteral("Status")),
      doubleSlider_{MIN, MAX},
      filterIntegers_{QStringLiteral("Integers Filter"), MIN, MAX},
      filterDoubles_{QStringLiteral("Doubles Filter"), MIN, MAX},
      filterDates_{QStringLiteral("Dates Filter"), startDate_, endDate_, true},
      filterStrings_{QStringLiteral("Names Filter"), exampleStringsList_},
      progressBarInfinite_{QStringLiteral("Title")},
      progressBarCounter_{QStringLiteral("Title"), MAX_PROGRESS_BAR_VALUE},
      startStopButtonInfinite_{QStringLiteral("start")},
      startStopButtonCounter_{QStringLiteral("start")}
{
    setWindowTitle(QString::fromLatin1("Wble library examples"));
    QHBoxLayout* widgetLayout{new QHBoxLayout()};
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

FilterNumbers* Examples::getFilterDoubles()
{
    QObject::connect(&filterDoubles_, &FilterDoubles::newNumericFilter, this,
                     &Examples::filterDoublesValuesChanged);

    filterDoubles_.setCheckable(true);
    return &filterDoubles_;
}

FilterDates* Examples::getFilterDates()
{
    QObject::connect(&filterDates_, &FilterDates::newDateFilter, this,
                     &Examples::filterDatesValuesChanged);

    filterDates_.setCheckable(true);
    return &filterDates_;
}

FilterStrings* Examples::getFilterStrings()
{
    QObject::connect(&filterStrings_, &FilterStrings::newStringFilter, this,
                     &Examples::filterStringsValuesChanged);

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
    leftLayout->addWidget(getFilterDoubles());
    leftLayout->addWidget(getFilterDates());
    leftLayout->addWidget(getFilterStrings());
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
    QObject::connect(&startStopButtonInfinite_, &QPushButton::clicked, this,
                     &Examples::infiniteButtonClicked);

    return wrapProgressBar(QStringLiteral("Infinite progress bar"),
                           &progressBarInfinite_, &startStopButtonInfinite_);
}

QGroupBox* Examples::createProgressBarCounter()
{
    progressCounterTimer_.setInterval(TIME_INTERVAL);
    QObject::connect(&progressCounterTimer_, &QTimer::timeout, this,
                     &Examples::counterTimerEvent);

    QObject::connect(&startStopButtonCounter_, &QPushButton::clicked, this,
                     &Examples::counterButtonClicked);

    return wrapProgressBar(QStringLiteral("Counter progress bar"),
                           &progressBarCounter_, &startStopButtonCounter_);
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

void Examples::filterDoublesValuesChanged(double min, double max)
{
    info_.setText("Doubles Filter: " + QString::number(min) + " | " +
                  QString::number(max));
}

void Examples::filterDatesValuesChanged(QDate from, QDate to,
                                        bool filterEmptyDates)
{
    QString msg{"Dates Filter: " + from.toString() + " | " + to.toString() +
                " | "};

    if (filterEmptyDates)
        msg.append(QString::fromLatin1("yes"));
    else
        msg.append(QString::fromLatin1("no"));

    info_.setText(msg);
}

void Examples::filterStringsValuesChanged(QStringList bannedItems)
{
    info_.setText("Names Filter: " + bannedItems.join(','));
}

void Examples::infiniteButtonClicked()
{
    const bool running{progressBarInfinite_.isRunning()};
    if (running)
    {
        progressBarInfinite_.stop();
        startStopButtonInfinite_.setText(QStringLiteral("start"));
    }
    else
    {
        progressBarInfinite_.start();
        startStopButtonInfinite_.setText(QStringLiteral("stop"));
    }
}

void Examples::counterButtonClicked()
{
    const bool running = progressBarCounter_.isRunning();
    if (running)
    {
        progressBarCounter_.stop();
        progressCounterTimer_.stop();
        startStopButtonCounter_.setText(QStringLiteral("start"));
    }
    else
    {
        progressBarCounter_.start();
        progressCounterTimer_.start();
        startStopButtonCounter_.setText(QStringLiteral("stop"));
    }
}

void Examples::counterTimerEvent()
{
    progressBarCounter_.updateProgress(progress_);
    if (progress_ >= MAX_PROGRESS_BAR_VALUE)
    {
        progress_ = 0;
        progressCounterTimer_.stop();
        startStopButtonCounter_.click();
    }
    else
    {
        ++progress_;
    }
}
