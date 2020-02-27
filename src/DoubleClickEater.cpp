#include "DoubleClickEater.h"

#include <QEvent>

DoubleClickEater::DoubleClickEater(QObject* parent) : QObject(parent)
{

}

bool DoubleClickEater::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
        return true;
    return QObject::eventFilter(obj, event);
}
