#pragma once

#include <QList>
#include <QObject>

class QLineEdit;

class FilterIntegersTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    static void testToggling();

    static void testChangingEditLinesValues();

    static void testReactionForMovingDoubleSlider();

private:
    static constexpr int fromValue_{0};
    static constexpr int toValue_{100};
};
