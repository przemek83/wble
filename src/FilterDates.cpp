#include <wble/FilterDates.h>

#include "ui_FilterDates.h"

FilterDates::FilterDates(const QString& name, QDate fromDate, QDate toDate,
                         bool emptyDates, QWidget* parent)
    : Filter{name, parent},
      fromDate_{fromDate},
      toDate_{toDate},
      ui_{std::make_unique<Ui::FilterDates>()},
      emptyDates_{emptyDates}
{
    ui_->setupUi(this);

    connect(ui_->ignoreEmptyDates, &QCheckBox::toggled, this,
            [this](bool checked)
            {
                Q_EMIT newDateFilter(ui_->fromDateEdit->date(),
                                     ui_->toDateEdit->date(), checked);
            });

    if (fromDate_ == toDate_)
        setDisabled(true);

    initFromDateCalendar();
    initToDateCalendar();

    ui_->ignoreEmptyDates->setVisible(emptyDates_);
    ui_->ignoreEmptyDates->setEnabled(emptyDates_);
}

FilterDates::~FilterDates() = default;

void FilterDates::initFromDateCalendar()
{
    calendarFrom_.setFirstDayOfWeek(Qt::Monday);
    calendarFrom_.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui_->fromDateEdit->setDate(fromDate_);
    ui_->fromDateEdit->setCalendarWidget(&calendarFrom_);
    connect(ui_->fromDateEdit, &QDateEdit::dateChanged, this,
            &FilterDates::fromDateChanged);
}

void FilterDates::initToDateCalendar()
{
    calendarTo_.setFirstDayOfWeek(Qt::Monday);
    calendarTo_.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui_->toDateEdit->setDate(toDate_);
    ui_->toDateEdit->setCalendarWidget(&calendarTo_);
    connect(ui_->toDateEdit, &QDateEdit::dateChanged, this,
            &FilterDates::toDateChanged);
}

void FilterDates::fromDateChanged(QDate newDate)
{
    if (newDate > ui_->toDateEdit->date())
        ui_->toDateEdit->setDate(newDate);

    Q_EMIT newDateFilter(ui_->fromDateEdit->date(), ui_->toDateEdit->date(),
                         ui_->ignoreEmptyDates->isChecked());
}

void FilterDates::toDateChanged(QDate newDate)
{
    if (newDate < ui_->fromDateEdit->date())
        ui_->fromDateEdit->setDate(newDate);

    Q_EMIT newDateFilter(ui_->fromDateEdit->date(), ui_->toDateEdit->date(),
                         ui_->ignoreEmptyDates->isChecked());
}

void FilterDates::checkedStateChanged(bool checked)
{
    const QList<QDateEdit*> dateWidgets{findChildren<QDateEdit*>()};

    for (QWidget* current : dateWidgets)
    {
        current->setVisible(checked);
        current->setEnabled(checked);
    }

    ui_->ignoreEmptyDates->setVisible(checked && emptyDates_);
    ui_->ignoreEmptyDates->setEnabled(checked);
}
