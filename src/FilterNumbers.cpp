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

    if (fmod(from, 1) != 0 || fmod(to, 1) != 0)
        doubleMode_ = true;

    initValidators();

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

void FilterNumbers::initValidators()
{
    QValidator* fromValidator {nullptr};
    QValidator* toValidator {nullptr};
    if (doubleMode_)
    {
        fromValidator = new QDoubleValidator(initialFromValue_, initialToValue_,
                                             2, ui->fromValue);
        toValidator = new QDoubleValidator(initialFromValue_, initialToValue_,
                                           2, ui->toValue);
    }
    else
    {
        const int from {static_cast<int>(initialFromValue_)};
        const int to {static_cast<int>(initialToValue_)};
        fromValidator = new QIntValidator(from, to, ui->fromValue);
        toValidator = new QIntValidator(from, to, ui->toValue);
    }
    ui->fromValue->setValidator(fromValidator);
    ui->toValue->setValidator(toValidator);
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
    if (doubleMode_)
    {
        ui->fromValue->setText(QLocale::system().toString(initialFromValue_, 'f', 2));
        ui->toValue->setText(QLocale::system().toString(initialToValue_, 'f', 2));
    }
    else
    {
        ui->fromValue->setText(QLocale::system().toString(static_cast<int>(initialFromValue_)));
        ui->toValue->setText(QLocale::system().toString(static_cast<int>(initialToValue_)));
    }

    connect(ui->fromValue, &QLineEdit::editingFinished,
            this, &FilterNumbers::fromEditingFinished);
    connect(ui->toValue, &QLineEdit::editingFinished,
            this, &FilterNumbers::toEditingFinished);
}

void FilterNumbers::emitChangeSignal()
{
    Q_EMIT newNumericFilter(QLocale::system().toDouble(ui->fromValue->text()),
                            QLocale::system().toDouble(ui->toValue->text()));
}

void FilterNumbers::sliderFromChanged(double newValue)
{
    if (doubleMode_)
        ui->fromValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui->fromValue->setText(QLocale::system().toString(newValue));

    emitChangeSignal();
}

void FilterNumbers::sliderToChanged(double newValue)
{
    if (doubleMode_)
        ui->toValue->setText(QLocale::system().toString(newValue, 'f', 2));
    else
        ui->toValue->setText(QLocale::system().toString(newValue));

    emitChangeSignal();
}

void FilterNumbers::fromEditingFinished()
{
    auto slider {findChild<DoubleSlider*>()};
    if (slider == nullptr)
        return;

    QString newFromAsText {ui->fromValue->text()};
    double fromToSet {doubleMode_ ?
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
    double toToSet {doubleMode_ ?
                    QLocale::system().toDouble(newToAsText) :
                    QLocale::system().toInt(newToAsText)};

    slider->setCurrentMax(toToSet);
    emitChangeSignal();
}
