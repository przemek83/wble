#include "Filter.h"

#include <QDebug>

Filter::Filter(const QString& title, QWidget* parent) :
    QGroupBox(title, parent)
{
    setCheckable(true);
}
