#include "FilterNumbers.h"

#include <cmath>

#include <DoubleSlider.h>
#include <QDebug>
#include <QIntValidator>

#include "ui_FilterNumbers.h"
#include "Utilities.h"

FilterNumbers::FilterNumbers(const QString& name,
                             double from,
                             double to,
                             QWidget* parent) :
    Filter(name, parent),
    ui(new Ui::FilterNumbers),
    initialFromValue_(from),
    initialToValue_(to)
{
    ui->setupUi(this);

    initLineEdits();

    initDoubleSlider();

    if (Utilities::doublesAreEqual(initialFromValue_, initialToValue_))
        setDisabled(true);
}

FilterNumbers::~FilterNumbers()
{
    delete ui;
}

void FilterNumbers::checkedStateChanged(bool checked)
{
    const QList<QWidget*> widgets {findChildren<QWidget*>()};

    for (QWidget* current : widgets)
        current->setVisible(checked);
}

QLineEdit* FilterNumbers::getFromLineEdit() const
{
    return ui->fromValue;
}

QLineEdit* FilterNumbers::getToLineEdit() const
{
    return ui->toValue;
}

void FilterNumbers::initDoubleSlider()
{
    DoubleSlider* slider {new DoubleSlider(initialFromValue_, initialToValue_, this)};
    connect(slider, &DoubleSlider::currentMinChanged,
            this, &FilterNumbers::sliderFromChanged);
    connect(slider, &DoubleSlider::currentMaxChanged,
            this, &FilterNumbers::sliderToChanged);

    ui->verticalLayout->addWidget(slider);
}

void FilterNumbers::initLineEdits()
{
    connect(ui->fromValue, &QLineEdit::editingFinished,
            this, &FilterNumbers::fromEditingFinished);
    connect(ui->toValue, &QLineEdit::editingFinished,
            this, &FilterNumbers::toEditingFinished);
}

void FilterNumbers::sliderFromChanged(double newValue)
{
    if (isDoubleMode())
        ui->fromValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui->fromValue->setText(QLocale::system().toString(static_cast<int>(newValue)));

    emitChangeSignal();
}

void FilterNumbers::sliderToChanged(double newValue)
{
    if (isDoubleMode())
        ui->toValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui->toValue->setText(QLocale::system().toString(static_cast<int>(newValue)));

    emitChangeSignal();
}

void FilterNumbers::fromEditingFinished()
{
    auto slider {findChild<DoubleSlider*>()};
    if (slider == nullptr)
        return;

    QString newFromAsText {ui->fromValue->text()};
    double fromToSet {isDoubleMode() ?
                      QLocale::system().toDouble(newFromAsText) :
                      QLocale::system().toInt(newFromAsText)};

    slider->setCurrentMin(fromToSet);
    emitChangeSignal();
}

void FilterNumbers::toEditingFinished()
{
    auto slider {findChild<DoubleSlider*>()};
    if (slider == nullptr)
        return;

    QString newToAsText = ui->toValue->text();
    double toToSet {isDoubleMode() ?
                    QLocale::system().toDouble(newToAsText) :
                    QLocale::system().toInt(newToAsText)};

    slider->setCurrentMax(toToSet);
    emitChangeSignal();
}
