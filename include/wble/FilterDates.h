#pragma once

#include <memory>

#include <QCalendarWidget>
#include <QDate>

#include "Filter.h"
#include "wble_global.h"

namespace Ui
{
class FilterDates;
}  // namespace Ui

/// @class FilterDates
/// @brief Filter for date type.
class WBLE_EXPORT FilterDates : public Filter
{
    Q_OBJECT
public:
    FilterDates(const QString& name, QDate fromDate, QDate toDate,
                bool emptyDates, QWidget* parent);
    FilterDates(const QString& name, QDate fromDate, QDate toDate,
                bool emptyDates);

    ~FilterDates() override;

Q_SIGNALS:
    /// Emitted when filter state was changed.
    /// @param fromDate Current from date.
    /// @param toDate Current to date.
    /// @param filterEmptyDates Flag indicating that data with empty date should
    /// be ignored.
    void newDateFilter(QDate fromDate, QDate toDate, bool filterEmptyDates);

protected:
    void checkedStateChanged(bool checked) override;

private:
    void initFromDateCalendar();

    void initToDateCalendar();

    /// Initial filter from date.
    const QDate fromDate_;

    /// Initial filter to date.
    const QDate toDate_;

    std::unique_ptr<Ui::FilterDates> ui_;

    QCalendarWidget calendarFrom_;

    QCalendarWidget calendarTo_;

    /// Flag indicating there are empty dates in data.
    const bool emptyDates_;

private Q_SLOTS:
    /// Triggered on change of date in from date edit.
    /// @param newDate New value.
    void fromDateChanged(QDate newDate);

    /// Triggered on change of date in to date edit.
    /// @param newDate New value.
    void toDateChanged(QDate newDate);
};
