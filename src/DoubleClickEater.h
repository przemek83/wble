#pragma once

#include <QObject>

class DoubleClickEater : public QObject
{
    Q_OBJECT
public:
    explicit DoubleClickEater(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
};
