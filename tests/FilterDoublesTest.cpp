#include "FilterDoublesTest.h"

#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>

#include <wble/DoubleSlider.h>
#include <wble/FilterDoubles.h>

#include "FilterNumbersCommon.h"

using FilterNumbersCommon::checkChangingEditLinesValues;
using FilterNumbersCommon::checkReactionForMovingDoubleSlider;
using FilterNumbersCommon::checkToggling;

void FilterDoublesTest::testToggling()
{
    checkToggling<FilterDoubles, double>(fromValue_, toValue_);
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
