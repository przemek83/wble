#include "FilterDates.h"

#include "ui_FilterDates.h"

FilterDates::FilterDates(const QString& name,
                         QDate fromDate,
                         QDate toDate,
                         bool emptyDates,
                         QWidget* parent) :
    Filter(name, parent),
    fromDate_(fromDate),
    toDate_(toDate),
    ui(new Ui::FilterDates),
    emptyDates_(emptyDates)
{
    ui->setupUi(this);

    connect(ui->ignoreEmptyDates, &QCheckBox::toggled,
            this, [ = ](bool checked)
    {
        Q_EMIT newDateFilter(ui->fromDateEdit->date(),
                             ui->toDateEdit->date(),
                             checked);
    });

    if (fromDate_ == toDate_)
        setDisabled(true);

    initFromDateCalendar();
    initToDateCalendar();

    ui->ignoreEmptyDates->setVisible(emptyDates_);
    ui->ignoreEmptyDates->setEnabled(emptyDates_);
}

FilterDates::~FilterDates()
{
    delete ui;
}

void FilterDates::initFromDateCalendar()
{
    calendarFrom_.setFirstDayOfWeek(Qt::Monday);
    calendarFrom_.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui->fromDateEdit->setDate(fromDate_);
    ui->fromDateEdit->setCalendarWidget(&calendarFrom_);
    connect(ui->fromDateEdit, &QDateEdit::dateChanged,
            this, &FilterDates::fromDateChanged);
}

void FilterDates::initToDateCalendar()
{
    calendarTo_.setFirstDayOfWeek(Qt::Monday);
    calendarTo_.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui->toDateEdit->setDate(toDate_);
    ui->toDateEdit->setCalendarWidget(&calendarTo_);
    connect(ui->toDateEdit, &QDateEdit::dateChanged,
            this, &FilterDates::toDateChanged);
}

void FilterDates::fromDateChanged(QDate newDate)
{
    if (newDate > ui->toDateEdit->date())
        ui->toDateEdit->setDate(newDate);

    Q_EMIT newDateFilter(ui->fromDateEdit->date(),
                         ui->toDateEdit->date(),
                         ui->ignoreEmptyDates->isChecked());
}

void FilterDates::toDateChanged(QDate newDate)
{
    if (newDate < ui->fromDateEdit->date())
        ui->fromDateEdit->setDate(newDate);

    Q_EMIT newDateFilter(ui->fromDateEdit->date(),
                         ui->toDateEdit->date(),
                         ui->ignoreEmptyDates->isChecked());
}

void FilterDates::checkedStateChanged(bool checked)
{
    QList<QDateEdit*> dateWidgets = findChildren<QDateEdit*>();

    for (QWidget* current : dateWidgets)
    {
        current->setVisible(checked);
        current->setEnabled(checked);
    }

    ui->ignoreEmptyDates->setVisible(checked && emptyDates_);
    ui->ignoreEmptyDates->setEnabled(checked);
}
