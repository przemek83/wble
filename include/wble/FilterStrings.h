#pragma once

#include <memory>

#include <QSet>

#include "Filter.h"
#include "wble_global.h"

class QListWidgetItem;
class DoubleClickEater;

namespace Ui
{
class FilterStrings;
}  // namespace Ui

/**
 * @class FilterNames
 * @brief Names filter for strings.
 */
class WBLE_EXPORT FilterStrings : public Filter
{
    Q_OBJECT
public:
    FilterStrings(const QString& name, QStringList initialList,
                  QWidget* parent = nullptr);

    ~FilterStrings() override;

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

    void initItems();

    int getLongestItemWitdth() const;

    const QStringList initialList_;

    QStringList lastEmittedList_;

    std::unique_ptr<Ui::FilterStrings> ui_;

    /// Min number of chars to include scroll margin.
    static constexpr int minNameWidthForScrollMargin_{25};

    /// Maximum widget heigh.
    static constexpr int maximumHeigh_{180};

    /// Flag indicating that additional place for scroll should be added.
    bool addMarginForScrollBar_;

    std::unique_ptr<DoubleClickEater> doubleClickEater_;

private Q_SLOTS:
    /**
     * Triggered when user click on item.
     * @param item Item clicked.
     */
    void itemChecked(const QListWidgetItem* item);

    /**
     * Triggered when user click on select all checkbox.
     * @param checked Checked state.
     */
    void selectAllToggled(bool checked);
};
