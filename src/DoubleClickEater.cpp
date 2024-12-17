#include "DoubleClickEater.h"

#include <QEvent>

DoubleClickEater::DoubleClickEater(QObject* parent) : QObject(parent) {}

bool DoubleClickEater::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
        return true;
    return QObject::eventFilter(watched, event);
}
