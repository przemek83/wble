#include <wble/FilterStrings.h>

#include <algorithm>

#include <QDebug>
#include <QListWidgetItem>
#include <QScrollBar>

#include "DoubleClickEater.h"
#include "ui_FilterStrings.h"

FilterStrings::FilterStrings(const QString& name, QStringList initialList,
                             QWidget* parent)
    : Filter{name, parent},
      initialList_{std::move(initialList)},
      ui_{std::make_unique<Ui::FilterStrings>()},
      addMarginForScrollBar_{false},
      doubleClickEater_{std::make_unique<DoubleClickEater>()}
{
    ui_->setupUi(this);

    connect(ui_->selectAll, &QCheckBox::toggled, this,
            &FilterStrings::selectAllToggled);

    initItems();

    if (int longestNameWidth{getLongestItemWitdth()};
        minNameWidthForScrollMargin_ <= longestNameWidth)
        addMarginForScrollBar_ = true;

    ui_->listWidget->viewport()->installEventFilter(&*doubleClickEater_);

    auto setAlternativeState{[this](QListWidgetItem* item)
                             {
                                 Qt::CheckState state{Qt::Checked};
                                 if (item->checkState() == Qt::Checked)
                                     state = Qt::Unchecked;
                                 item->setCheckState(state);
                                 itemChecked(item);
                             }};
    connect(ui_->listWidget, &QListWidget::itemClicked, this,
            setAlternativeState);
    connect(ui_->listWidget, &QListWidget::itemActivated, this,
            setAlternativeState);

    if (initialList_.size() <= 1)
    {
        ui_->selectAll->hide();
        ui_->selectAll->setEnabled(false);
    }
}

FilterStrings::~FilterStrings() = default;

void FilterStrings::itemChecked(const QListWidgetItem* item)
{
    if (item == nullptr)
        return;

    const QStringList currentList{getListOfSelectedItems()};

    // If sizes are same it means nothing happen lately.
    if (currentList.count() == lastEmittedList_.count())
        return;

    updateSelectAllCheckbox();

    lastEmittedList_ = currentList;
    Q_EMIT newStringFilter(lastEmittedList_);
}

QSize FilterStrings::sizeHint() const
{
    if (isChecked())
    {
        int maxListHeight{std::min(
            (ui_->listWidget->sizeHintForRow(0) * ui_->listWidget->count()) +
                (2 * ui_->listWidget->frameWidth()),
            maximumHeigh_)};

        // Add space for scroll in case of 3 or less items and long
        //   names detected in constructor.
        if (addMarginForScrollBar_ && (3 >= ui_->listWidget->count()))
        {
            // Scroll size retrieved here is not actual one, use row heigh
            // instead.
            maxListHeight += ui_->listWidget->sizeHintForRow(0);
        }

        ui_->listWidget->setMaximumHeight(maxListHeight);
    }
    return QGroupBox::sizeHint();
}

void FilterStrings::checkedStateChanged(bool checked)
{
    auto* checkBox{findChild<QCheckBox*>()};

    QList<QWidget*> widgets{findChildren<QWidget*>()};
    widgets.removeOne(checkBox);

    for (QWidget* current : widgets)
    {
        current->setVisible(checked);
        current->setEnabled(checked);
    }

    ui_->selectAll->setVisible(checked && (initialList_.size() > 1));
    ui_->selectAll->setEnabled(checked);
}

QStringList FilterStrings::getListOfSelectedItems() const
{
    QStringList currentList;
    const int itemCount{ui_->listWidget->count()};
    currentList.reserve(itemCount);
    for (int i = 0; i < itemCount; ++i)
    {
        const QListWidgetItem* currentItem{ui_->listWidget->item(i)};
        if (Qt::Unchecked == currentItem->checkState())
            currentList << currentItem->text();
    }

    return currentList;
}

void FilterStrings::updateSelectAllCheckbox()
{
    bool allChecked{true};
    const int itemCount{ui_->listWidget->count()};
    for (int i = 0; i < itemCount; ++i)
    {
        if (Qt::Unchecked == ui_->listWidget->item(i)->checkState())
        {
            allChecked = false;
            break;
        }
    }
    ui_->selectAll->blockSignals(true);
    if (allChecked)
        ui_->selectAll->setCheckState(Qt::Checked);
    else
        ui_->selectAll->setCheckState(Qt::Unchecked);
    ui_->selectAll->blockSignals(false);
}

void FilterStrings::initItems()
{
    ui_->listWidget->addItems(initialList_);
    const int itemsCount{ui_->listWidget->count()};
    for (int i{0}; i < itemsCount; ++i)
    {
        QListWidgetItem* item{ui_->listWidget->item(i)};
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
    }
}

int FilterStrings::getLongestItemWitdth() const
{
    int longestNameWidth{0};
    for (const QString& itemName : initialList_)
        longestNameWidth =
            static_cast<int>(::qMax(longestNameWidth, itemName.length()));
    return longestNameWidth;
}

void FilterStrings::selectAllToggled(bool checked)
{
    Q_ASSERT(ui_->listWidget->count() > 0);

    ui_->listWidget->blockSignals(true);
    const int itemCount{ui_->listWidget->count()};
    for (int i = 0; i < itemCount; ++i)
    {
        if (checked)
            ui_->listWidget->item(i)->setCheckState(Qt::Checked);
        else
            ui_->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
    ui_->listWidget->blockSignals(false);
    itemChecked(ui_->listWidget->item(0));
}
