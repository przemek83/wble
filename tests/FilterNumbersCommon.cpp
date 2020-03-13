#include "FilterNumbersCommon.h"

namespace FilterNumbersCommon
{
std::tuple<QLineEdit*, QLineEdit*> getLineEdits(QList<QLineEdit*> lineEdits,
                                                int fromValue,
                                                int toValue)
{
    const int firstValue =
        QLocale::system().toInt(lineEdits.first()->text());
    QLineEdit* fromEdit = (firstValue == fromValue ?
                           lineEdits.first() : lineEdits.last());
    QLineEdit* toEdit = (firstValue == toValue ?
                         lineEdits.first() : lineEdits.last());
    return {fromEdit, toEdit};
}

}  // namespace FilterNumbersCommon
