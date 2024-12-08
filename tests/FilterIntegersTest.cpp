#include "FilterIntegersTest.h"

#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>

#include <wble/DoubleSlider.h>
#include <wble/FilterIntegers.h>

#include "FilterNumbersCommon.h"

using FilterNumbersCommon::checkChangingEditLinesValues;
using FilterNumbersCommon::checkReactionForMovingDoubleSlider;
using FilterNumbersCommon::checkToggling;

void FilterIntegersTest::testToggling()
{
    checkToggling<FilterIntegers, int>(fromValue_, toValue_);
}

void FilterIntegersTest::testChangingEditLinesValues()
{
    checkChangingEditLinesValues<FilterIntegers, int>(fromValue_, toValue_);
}

void FilterIntegersTest::testReactionForMovingDoubleSlider()
{
    checkReactionForMovingDoubleSlider<FilterIntegers, int>(fromValue_,
                                                            toValue_);
}
