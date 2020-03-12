#include "FilterStrings.h"

#include <algorithm>

#include <QDebug>
#include <QListWidgetItem>
#include <QScrollBar>

#include "DoubleClickEater.h"
#include "ui_FilterStrings.h"

FilterStrings::FilterStrings(const QString& name,
                             QStringList initialList,
                             QWidget* parent) :
    Filter(name, parent),
    initialList_(std::move(initialList)),
    ui(new Ui::FilterStrings),
    addMarginForScrollBar_(false)
{
    ui->setupUi(this);

    connect(ui->selectAll, &QCheckBox::toggled, this, &FilterStrings::selectAllToggled);

    int longestNameWidth {0};
    for (const QString& itemName : initialList_)
    {
        auto item = new QListWidgetItem(itemName, ui->listWidget);
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        longestNameWidth = qMax(longestNameWidth, itemName.length());
    }

    if (minNameWidthForScrollMargin_ <= longestNameWidth)
        addMarginForScrollBar_ = true;

    ui->listWidget->viewport()->installEventFilter(new DoubleClickEater(ui->listWidget));

    auto setAlternativeState =
        [ = ](QListWidgetItem * item)
    {
        item->setCheckState((item->checkState() == Qt::Checked ?
                             Qt::Unchecked : Qt::Checked));
        itemChecked(item);
    };
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, setAlternativeState);
    connect(ui->listWidget, &QListWidget::itemActivated,
            this, setAlternativeState);

    if (initialList_.size() <= 1)
    {
        ui->selectAll->hide();
        ui->selectAll->setEnabled(false);
    }
}

FilterStrings::~FilterStrings()
{
    delete ui;
}

void FilterStrings::itemChecked(QListWidgetItem* item)
{
    if (item == nullptr)
        return;

    const QStringList currentList {getListOfSelectedItems()};

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
        int maxListHeight =
            std::min(ui->listWidget->sizeHintForRow(0) *
                     ui->listWidget->count() + 2 * ui->listWidget->frameWidth(),
                     maximumHeigh_);

        /* Add space for scroll in case of 3 or less items and long
           names detected in constructor.*/
        if (addMarginForScrollBar_ && 3 >= ui->listWidget->count())
        {
            //Scroll size retrieved here is not actual one, use rtow heigh instead.
            maxListHeight += ui->listWidget->sizeHintForRow(0);
        }

        ui->listWidget->setMaximumHeight(maxListHeight);
    }
    return QGroupBox::sizeHint();
}

void FilterStrings::checkedStateChanged(bool checked)
{
    auto checkBox = findChild<QCheckBox*>();

    QList<QWidget*> widgets = findChildren<QWidget*>();
    widgets.removeOne(checkBox);

    for (QWidget* current : widgets)
    {
        current->setVisible(checked);
        current->setEnabled(checked);
    }

    ui->selectAll->setVisible(checked && initialList_.size() > 1);
    ui->selectAll->setEnabled(checked);
}

QStringList FilterStrings::getListOfSelectedItems() const
{
    QStringList currentList;
    currentList.reserve(ui->listWidget->count());
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem* currentItem = ui->listWidget->item(i);
        if (Qt::Unchecked == currentItem->checkState())
            currentList << currentItem->text();
    }

    return currentList;
}

void FilterStrings::updateSelectAllCheckbox()
{
    bool allChecked {true};
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        if (Qt::Unchecked == ui->listWidget->item(i)->checkState())
        {
            allChecked = false;
            break;
        }
    }
    ui->selectAll->blockSignals(true);
    ui->selectAll->setCheckState((allChecked ? Qt::Checked : Qt::Unchecked));
    ui->selectAll->blockSignals(false);
}

void FilterStrings::selectAllToggled(bool checked)
{
    Q_ASSERT(ui->listWidget->count() > 0);

    ui->listWidget->blockSignals(true);
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        if (checked)
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        else
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
    ui->listWidget->blockSignals(false);
    itemChecked(ui->listWidget->item(0));
}
