#include "FilterIntegers.h"

#include <QIntValidator>
#include <QLineEdit>

FilterIntegers::FilterIntegers(const QString& name,
                               double from,
                               double to,
                               QWidget* parent) :
    FilterNumbers(name, from, to, parent)
{
    QLineEdit* fromLineEdit = getFromLineEdit();
    QLineEdit* toLineEdit = getToLineEdit();

    const int fromInt {static_cast<int>(from)};
    const int toInt {static_cast<int>(to)};
    QValidator* fromValidator = new QIntValidator(fromInt, toInt, fromLineEdit);
    QValidator* toValidator = new QIntValidator(fromInt, toInt, toLineEdit);
    fromLineEdit->setValidator(fromValidator);
    toLineEdit->setValidator(toValidator);

    fromLineEdit->setText(QLocale::system().toString(static_cast<int>(from)));
    toLineEdit->setText(QLocale::system().toString(static_cast<int>(to)));
}

bool FilterIntegers::isDoubleMode() const
{
    return false;
}

void FilterIntegers::emitChangeSignal()
{
    QLineEdit* fromLineEdit = getFromLineEdit();
    QLineEdit* toLineEdit = getToLineEdit();

    Q_EMIT newNumericFilter(QLocale::system().toInt(fromLineEdit->text()),
                            QLocale::system().toInt(toLineEdit->text()));
}
