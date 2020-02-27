#ifndef DOUBLECLICKEATER_H
#define DOUBLECLICKEATER_H

#include <QObject>

class DoubleClickEater : public QObject
{
    Q_OBJECT
public:
    explicit DoubleClickEater(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // DOUBLECLICKEATER_H
