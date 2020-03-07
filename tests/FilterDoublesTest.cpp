#include "FilterDoublesTest.h"

#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "DoubleSlider.h"
#include "FilterDoubles.h"

#include "FilterNumbersCommon.h"

using namespace FilterNumbersCommon;

void FilterDoublesTest::testToggling()
{
    checkToggling<FilterDoubles, double> (fromValue_, toValue_);
}

void FilterDoublesTest::testChangingEditLinesValues()
{
    checkChangingEditLinesValues<FilterDoubles, double>(fromValue_, toValue_);
}

void FilterDoublesTest::testReactionForMovingDoubleSlider()
{
    checkReactionForMovingDoubleSlider<FilterDoubles, double>(fromValue_,
                                                              toValue_);

}
