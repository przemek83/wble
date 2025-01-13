#include <wble/FilterIntegers.h>

#include <QLineEdit>

FilterIntegers::FilterIntegers(const QString& name, double from, double to,
                               QWidget* parent)
    : FilterNumbers{name, from, to, parent}
{
    const int fromInt{static_cast<int>(from)};
    const int toInt{static_cast<int>(to)};
    fromValidator_.setRange(fromInt, toInt);
    toValidator_.setRange(fromInt, toInt);

    QLineEdit* fromLineEdit{getFromLineEdit()};
    fromLineEdit->setValidator(&fromValidator_);
    fromLineEdit->setText(QLocale::system().toString(fromInt));

    QLineEdit* toLineEdit{getToLineEdit()};
    toLineEdit->setValidator(&toValidator_);
    toLineEdit->setText(QLocale::system().toString(toInt));
}

FilterIntegers::FilterIntegers(const QString& name, double from, double to)
    : FilterIntegers(name, from, to, nullptr)
{
}

bool FilterIntegers::isDoubleMode() const { return false; }

void FilterIntegers::emitChangeSignal()
{
    const QString fromText{getFromLineEdit()->text()};
    const QString toText{getToLineEdit()->text()};

    Q_EMIT newNumericFilter(QLocale::system().toInt(fromText),
                            QLocale::system().toInt(toText));
}
