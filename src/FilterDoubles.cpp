#include <qobject.h>
#include <wble/FilterDoubles.h>

#include <QLineEdit>

FilterDoubles::FilterDoubles(const QString& name, double from, double to,
                             QWidget* parent)
    : FilterNumbers{name, from, to, parent},
      fromValidator_{from, to, getDecimalPlaces()},
      toValidator_{from, to, getDecimalPlaces()}
{
    QLineEdit* fromLineEdit{getFromLineEdit()};
    fromLineEdit->setValidator(&fromValidator_);
    fromLineEdit->setText(
        QLocale::system().toString(from, 'f', getDecimalPlaces()));

    QLineEdit* toLineEdit{getToLineEdit()};
    toLineEdit->setValidator(&toValidator_);
    toLineEdit->setText(
        QLocale::system().toString(to, 'f', getDecimalPlaces()));
}

bool FilterDoubles::isDoubleMode() const { return true; }

void FilterDoubles::emitChangeSignal()
{
    const QString fromText{getFromLineEdit()->text()};
    const QString toText{getToLineEdit()->text()};

    Q_EMIT newNumericFilter(QLocale::system().toDouble(fromText),
                            QLocale::system().toDouble(toText));
}
