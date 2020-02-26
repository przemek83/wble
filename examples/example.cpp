#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWindow>

#include "DoubleSlider.h"
#include "FilterNumbers.h"
#include "FilterDates.h"
#include "FilterNames.h"

static const double MIN {-100.};
static const double MAX {100.};

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

static FilterNumbers* createFilterNumbers(QLabel* infoLabel)
{
    auto filterNumbers = new FilterNumbers("Numbers Filter", MIN, MAX);
    QObject::connect(filterNumbers,
                     &FilterNumbers::newNumericFilter,
                     infoLabel,
                     [ = ](double min, double max)
    {
        infoLabel->setText("Numbers Filter: " + QString::number(min) + " | " +
                           QString::number(max));
    });

    filterNumbers->setCheckable(true);
    return filterNumbers;
}

static FilterDates* createFilterDates(QLabel* infoLabel)
{
    auto filterDates = new FilterDates("Dates Filter",
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

static FilterNames* createFilterNames(QLabel* infoLabel)
{
    auto filterNames =
        new FilterNames("Names Filter", QStringList{"a", "b", "c", "d"});
    QObject::connect(filterNames,
                     &FilterNames::newStringFilter,
                     infoLabel,
                     [ = ](QStringList bannedItems)
    {
        infoLabel->setText("Names Filter: " + bannedItems.join(","));
    });

    filterNames->setCheckable(true);
    return filterNames;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QWidget widget;

    auto infoLabel = new QLabel("Status");
    QVBoxLayout widgetLayout(&widget);
    widgetLayout.setSpacing(10);
    QGroupBox groupBox(QStringLiteral("Double Slider"));
    QVBoxLayout layout(&groupBox);
    layout.addWidget(createDoubleSlider(infoLabel));
    groupBox.setLayout(&layout);
    widgetLayout.addWidget(&groupBox);
    widgetLayout.addWidget(createFilterNumbers(infoLabel));
    widgetLayout.addWidget(createFilterDates(infoLabel));
    widgetLayout.addWidget(createFilterNames(infoLabel));
    widgetLayout.addWidget(infoLabel);
    widgetLayout.addStretch();
    widget.setLayout(&widgetLayout);
    widget.show();

    return QApplication::exec();
}
