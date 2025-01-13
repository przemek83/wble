#pragma once

#include <QObject>

class DoubleClickEater : public QObject
{
    Q_OBJECT
public:
    DoubleClickEater();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
};
