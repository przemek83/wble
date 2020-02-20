#ifndef CONSTANTSTEST_H
#define CONSTANTSTEST_H

#include <QObject>

/**
 * @brief Unit test for Constants class.
 */
class DoubleSliderTest: public QObject
{
    Q_OBJECT
private slots:
    void testSettingCurrentValues();

    void testEmittingCurrentMinChanged();

    void testEmittingCurrentMaxChanged();
};

#endif // CONSTANTSTEST_H
