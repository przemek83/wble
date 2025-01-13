#include "DoubleClickEater.h"

#include <QEvent>

DoubleClickEater::DoubleClickEater() : QObject(nullptr) {}

bool DoubleClickEater::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
        return true;
    return QObject::eventFilter(watched, event);
}
