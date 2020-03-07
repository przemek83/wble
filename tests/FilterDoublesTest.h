#ifndef FILTERDOUBLESTEST_H
#define FILTERDOUBLESTEST_H

#include <QList>
#include <QObject>

class QLineEdit;

class FilterDoublesTest: public QObject
{
    Q_OBJECT
private slots:
    void testToggling();

    void testChangingEditLinesValues();

    void testReactionForMovingDoubleSlider();

private:
    static constexpr double fromValue_ {0.};
    static constexpr double toValue_ {100.};
};


#endif // FILTERDOUBLESTEST_H
