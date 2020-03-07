#ifndef FILTERNAMES_H
#define FILTERNAMES_H

#include <QSet>

#include "Filter.h"
#include "wble_global.h"

class QListWidgetItem;

namespace Ui
{
class FilterStrings;
} // namespace Ui

/**
 * @class FilterNames
 * @brief Names filter for strings.
 */
class WBLE_EXPORT FilterStrings : public Filter
{
    Q_OBJECT
public:
    FilterStrings(const QString& name,
                  QStringList initialList,
                  QWidget* parent = nullptr);

    ~FilterStrings() override;

    FilterStrings& operator=(const FilterStrings& other) = delete;
    FilterStrings(const FilterStrings& other) = delete;

    FilterStrings& operator=(FilterStrings&& other) = delete;
    FilterStrings(FilterStrings&& other) = delete;

    QSize sizeHint() const override;

Q_SIGNALS:
    /**
     * Emitted when filter state was changed.
     * @param bannedList List of unchecked items.
     */
    void newStringFilter(QStringList bannedList);

protected:
    void checkedStateChanged(bool checked) override;

private:
    QStringList getListOfSelectedItems() const;

    void updateSelectAllCheckbox();

    const QStringList initialList_;

    QStringList lastEmittedList_;

    Ui::FilterStrings* ui;

    /// Min number of chars to include scrioll margin.
    static constexpr int minNameWidthForScrollMargin_ {25};

    /// Maximum widget heigh.
    static constexpr int maximumHeigh_ {180};

    /// Flag indocating if additionall place for scroll should be added.
    bool addMarginForScrollBar_;

private Q_SLOTS:
    /**
     * Triggered when user click on item.
     * @param item Item clicked.
     */
    void itemChecked(QListWidgetItem* item);

    /**
     * Triggered when user click on select all checkbox.
     * @param checked Checked state.
     */
    void selectAllToggled(bool checked);
};

#endif // FILTERNAMES_H
