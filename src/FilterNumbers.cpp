#include <wble/FilterNumbers.h>

#include <cmath>

#include <wble/DoubleSlider.h>
#include <QDebug>
#include <QIntValidator>

#include "Utilities.h"
#include "ui_FilterNumbers.h"

FilterNumbers::FilterNumbers(const QString& name, double from, double to,
                             QWidget* parent)
    : Filter(name, parent),
      ui_{std::make_unique<Ui::FilterNumbers>()},
      initialFromValue_(from),
      initialToValue_(to)
{
    ui_->setupUi(this);

    initLineEdits();

    initDoubleSlider();

    initColorForLineEdits();

    if (utilities::doublesAreEqual(initialFromValue_, initialToValue_))
        setDisabled(true);
}

FilterNumbers::~FilterNumbers() = default;

void FilterNumbers::checkedStateChanged(bool checked)
{
    const QList<QWidget*> widgets{findChildren<QWidget*>()};

    for (QWidget* widget : widgets)
    {
        widget->setEnabled(checked);
        widget->setVisible(checked);
    }
}

QLineEdit* FilterNumbers::getFromLineEdit() const { return ui_->fromValue; }

QLineEdit* FilterNumbers::getToLineEdit() const { return ui_->toValue; }

void FilterNumbers::changeEvent(QEvent* event)
{
    Filter::changeEvent(event);

    if (event->type() == QEvent::StyleChange)
        initColorForLineEdits();
}

void FilterNumbers::initDoubleSlider()
{
    DoubleSlider* slider{
        new DoubleSlider(initialFromValue_, initialToValue_, this)};
    connect(slider, &DoubleSlider::currentMinChanged, this,
            &FilterNumbers::sliderFromChanged);
    connect(slider, &DoubleSlider::currentMaxChanged, this,
            &FilterNumbers::sliderToChanged);

    ui_->verticalLayout->addWidget(slider);
}

void FilterNumbers::initLineEdits() const
{
    connect(ui_->fromValue, &QLineEdit::editingFinished, this,
            &FilterNumbers::fromEditingFinished);
    connect(ui_->toValue, &QLineEdit::editingFinished, this,
            &FilterNumbers::toEditingFinished);

    connect(ui_->fromValue, &QLineEdit::textChanged, this,
            &FilterNumbers::lineEditContentModified);
    connect(ui_->toValue, &QLineEdit::textChanged, this,
            &FilterNumbers::lineEditContentModified);
}

void FilterNumbers::initColorForLineEdits()
{
    const QPalette defaultPalette{QApplication::palette(ui_->fromValue)};
    defaultBackgroundColor_ =
        defaultPalette.color(ui_->fromValue->backgroundRole());
    altBackgroundColor_ = defaultPalette.color(QPalette::Highlight);
}

void FilterNumbers::sliderFromChanged(double newValue)
{
    if (isDoubleMode())
        ui_->fromValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui_->fromValue->setText(
            QLocale::system().toString(static_cast<int>(newValue)));

    emitChangeSignal();
}

void FilterNumbers::sliderToChanged(double newValue)
{
    if (isDoubleMode())
        ui_->toValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui_->toValue->setText(
            QLocale::system().toString(static_cast<int>(newValue)));

    emitChangeSignal();
}

void FilterNumbers::fromEditingFinished()
{
    auto* slider{findChild<DoubleSlider*>()};
    if (slider == nullptr)
        return;

    const QString newFromAsText{ui_->fromValue->text()};
    const double fromToSet{isDoubleMode()
                               ? QLocale::system().toDouble(newFromAsText)
                               : QLocale::system().toInt(newFromAsText)};

    slider->setCurrentMin(fromToSet);
    emitChangeSignal();
}

void FilterNumbers::toEditingFinished()
{
    auto* slider{findChild<DoubleSlider*>()};
    if (slider == nullptr)
        return;

    const QString newToAsText = ui_->toValue->text();
    const double toToSet{isDoubleMode()
                             ? QLocale::system().toDouble(newToAsText)
                             : QLocale::system().toInt(newToAsText)};

    slider->setCurrentMax(toToSet);
    emitChangeSignal();
}

void FilterNumbers::lineEditContentModified(const QString& currentContent) const
{
    auto* lineEdit = ::qobject_cast<QLineEdit*>(sender());
    const double currentValue = QLocale::system().toDouble(currentContent);
    QPalette palette = lineEdit->palette();
    const bool currentValueValid = (currentValue >= initialFromValue_) &&
                                   (currentValue <= initialToValue_);
    const QColor currentBackgroundColor{
        palette.color(lineEdit->backgroundRole())};
    if (currentValueValid && (currentBackgroundColor == altBackgroundColor_))
    {
        palette.setColor(lineEdit->backgroundRole(), defaultBackgroundColor_);
        lineEdit->setPalette(palette);
    }

    if ((!currentValueValid) &&
        (currentBackgroundColor == defaultBackgroundColor_))
    {
        palette.setColor(lineEdit->backgroundRole(), altBackgroundColor_);
        lineEdit->setPalette(palette);
    }
}
