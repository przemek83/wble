#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QTimer>
#include <QVBoxLayout>
#include <QWindow>

#include "DoubleSlider.h"
#include "FilterDates.h"
#include "FilterDoubles.h"
#include "FilterIntegers.h"
#include "FilterStrings.h"
#include "ProgressBarCounter.h"
#include "ProgressBarInfinite.h"

static constexpr double MIN {3};
static constexpr double MAX {56};

static constexpr int MAX_PROGRESS_BAR_VALUE {100};

static DoubleSlider* createDoubleSlider(QLabel* infoLabel)
{
    auto slider = new DoubleSlider(MIN, MAX);
    QObject::connect(slider,
                     &DoubleSlider::currentMinChanged,
                     infoLabel,
                     [ = ](double min)
    {
        infoLabel->setText("Double Slider: min = " + QString::number(min));
    });

    QObject::connect(slider,
                     &DoubleSlider::currentMaxChanged,
                     infoLabel,
                     [ = ](double max)
    {
        infoLabel->setText("Double Slider: max = " + QString::number(max));
    });

    return slider;
}

static FilterNumbers* createFilterIntegers(QLabel* infoLabel)
{
    auto filterNumbers =
        new FilterIntegers(QStringLiteral("Integers Filter"), MIN, MAX);
    QObject::connect(filterNumbers,
                     &FilterIntegers::newNumericFilter,
                     infoLabel,
                     [ = ](int min, int max)
    {
        infoLabel->setText("Integers Filter: " + QString::number(min) + " | " +
                           QString::number(max));
    });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

static FilterNumbers* createFilterDoubles(QLabel* infoLabel)
{
    auto filterNumbers =
        new FilterDoubles(QStringLiteral("Doubles Filter"), MIN, MAX);
    QObject::connect(filterNumbers,
                     &FilterDoubles::newNumericFilter,
                     infoLabel,
                     [ = ](double min, double max)
    {
        infoLabel->setText("Doubles Filter: " + QString::number(min) + " | " +
                           QString::number(max));
    });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

static FilterDates* createFilterDates(QLabel* infoLabel)
{
    auto filterDates = new FilterDates(QStringLiteral("Dates Filter"),
                                       QDate(2010, 9, 21),
                                       QDate(2012, 2, 25),
                                       true);
    QObject::connect(filterDates,
                     &FilterDates::newDateFilter,
                     infoLabel,
                     [ = ](QDate from, QDate to, bool filterEmptyDates)
    {
        infoLabel->setText("Dates Filter: " + from.toString() + " | " +
                           to.toString() + " | " +
                           (filterEmptyDates ? "yes" : "no"));
    });

    filterDates->setCheckable(true);
    return filterDates;
}

static FilterStrings* createFilterStrings(QLabel* infoLabel)
{
    auto filterNames =  new FilterStrings(QStringLiteral("Names Filter"),
                                          QStringList{QStringLiteral("a"),
                                                      QStringLiteral("b"),
                                                      QStringLiteral("c"),
                                                      QStringLiteral("d")});
    QObject::connect(filterNames,
                     &FilterStrings::newStringFilter,
                     infoLabel,
                     [ = ](const QStringList & bannedItems)
    {
        infoLabel->setText("Names Filter: " + bannedItems.join(','));
    });

    filterNames->setCheckable(true);
    return filterNames;
}

static QVBoxLayout* createLeftWidgetColumn(QLabel* infoLabel)
{
    auto leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(10);
    auto groupBox = new QGroupBox(QStringLiteral("Double Slider"));
    auto layout = new QVBoxLayout(groupBox);
    layout->addWidget(createDoubleSlider(infoLabel));
    groupBox->setLayout(layout);
    leftLayout->addWidget(groupBox);
    leftLayout->addWidget(createFilterIntegers(infoLabel));
    leftLayout->addWidget(createFilterDoubles(infoLabel));
    leftLayout->addWidget(createFilterDates(infoLabel));
    leftLayout->addWidget(createFilterStrings(infoLabel));
    leftLayout->addWidget(infoLabel);
    leftLayout->addStretch();
    return leftLayout;
}

static QGroupBox* wrapProgressBar(const QString& name,
                                  ProgressBar* progressBar,
                                  QPushButton* startStopButton)
{
    auto groupBox = new QGroupBox(name);
    auto layout = new QVBoxLayout();
    layout->addWidget(progressBar);
    layout->addWidget(startStopButton);
    groupBox->setLayout(layout);
    return groupBox;
}

static QGroupBox* createProgressBarInfinite()
{
    auto progressBar = new ProgressBarInfinite(QStringLiteral("Title"));
    auto startStopButton = new QPushButton(QStringLiteral("start"));
    QObject::connect(startStopButton, &QPushButton::clicked, progressBar,
                     [ = ]()
    {
        const bool running = progressBar->isRunning();
        if (running)
            progressBar->stop();
        else
            progressBar->start();
        startStopButton->setText((running ?
                                  QStringLiteral("start") :
                                  QStringLiteral("stop")));

    });
    return wrapProgressBar(QStringLiteral("Infinite progress bar"),
                           progressBar,
                           startStopButton);
}

static QGroupBox* createProgressBarCounter()
{
    auto progressBar =
        new ProgressBarCounter(QStringLiteral("Title"), MAX_PROGRESS_BAR_VALUE);
    auto startStopButton = new QPushButton(QStringLiteral("start"));
    auto timer = new QTimer(progressBar);
    timer->setInterval(40);
    QObject::connect(timer, &QTimer::timeout, progressBar,
                     [ = ]()
    {
        static int progress {0};
        progressBar->updateProgress(progress);
        progress++;
        if (progress > MAX_PROGRESS_BAR_VALUE)
        {
            timer->stop();
            progress = 0;
            startStopButton->click();
        }
    });
    QObject::connect(startStopButton, &QPushButton::clicked, progressBar,
                     [ = ]()
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
        startStopButton->setText((running ?
                                  QStringLiteral("start") :
                                  QStringLiteral("stop")));

    });
    return wrapProgressBar(QStringLiteral("Counter progress bar"),
                           progressBar,
                           startStopButton);
}

static QVBoxLayout* createRightWidgetColumn()
{
    auto rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(10);
    rightLayout->addWidget(createProgressBarInfinite());
    rightLayout->addWidget(createProgressBarCounter());
    rightLayout->addStretch();
    return rightLayout;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QWidget widget;
    auto infoLabel = new QLabel(QStringLiteral("Status"));
    QHBoxLayout widgetLayout(&widget);
    QVBoxLayout* leftWidgetColumn = createLeftWidgetColumn(infoLabel);
    widgetLayout.addLayout(leftWidgetColumn);
    QVBoxLayout* rightWidgetColumn = createRightWidgetColumn();
    widgetLayout.addLayout(rightWidgetColumn);
    widget.setLayout(&widgetLayout);
    widget.show();

    return QApplication::exec();
}
