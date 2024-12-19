#include <wble/FilterDoubles.h>

#include <QLineEdit>

FilterDoubles::FilterDoubles(const QString& name, double from, double to,
                             QWidget* parent)
    : FilterNumbers(name, from, to, parent),
      fromValidator_{from, to, decimalPlaces_},
      toValidator_{from, to, decimalPlaces_}
{
    QLineEdit* fromLineEdit = getFromLineEdit();
    fromLineEdit->setValidator(&fromValidator_);
    fromLineEdit->setText(
        QLocale::system().toString(from, 'f', decimalPlaces_));

    QLineEdit* toLineEdit = getToLineEdit();
    toLineEdit->setValidator(&toValidator_);
    toLineEdit->setText(QLocale::system().toString(to, 'f', decimalPlaces_));
}

bool FilterDoubles::isDoubleMode() const { return true; }

void FilterDoubles::emitChangeSignal()
{
    const QLineEdit* fromLineEdit = getFromLineEdit();
    const QLineEdit* toLineEdit = getToLineEdit();

    Q_EMIT newNumericFilter(QLocale::system().toDouble(fromLineEdit->text()),
                            QLocale::system().toDouble(toLineEdit->text()));
}
