#include "FilterDoubles.h"

#include <QDoubleValidator>
#include <QLineEdit>

FilterDoubles::FilterDoubles(const QString& name,
                             double from,
                             double to,
                             QWidget* parent) :
    FilterNumbers(name, from, to, parent)
{
    QLineEdit* fromLineEdit = getFromLineEdit();
    QLineEdit* toLineEdit = getToLineEdit();

    QValidator* fromValidator = new QDoubleValidator(from, to, 2, fromLineEdit);
    QValidator* toValidator = new QDoubleValidator(from, to, 2, toLineEdit);

    fromLineEdit->setValidator(fromValidator);
    toLineEdit->setValidator(toValidator);

    fromLineEdit->setText(QLocale::system().toString(from, 'f', 2));
    toLineEdit->setText(QLocale::system().toString(to, 'f', 2));
}

bool FilterDoubles::isDoubleMode() const
{
    return true;
}


void FilterDoubles::emitChangeSignal()
{
    QLineEdit* fromLineEdit = getFromLineEdit();
    QLineEdit* toLineEdit = getToLineEdit();

    Q_EMIT newNumericFilter(QLocale::system().toDouble(fromLineEdit->text()),
                            QLocale::system().toDouble(toLineEdit->text()));
}

