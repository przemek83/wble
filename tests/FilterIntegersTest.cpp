#include "FilterIntegersTest.h"

#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>

#include "DoubleSlider.h"
#include "FilterIntegers.h"

#include "FilterNumbersCommon.h"

using FilterNumbersCommon::checkToggling;
using FilterNumbersCommon::checkChangingEditLinesValues;
using FilterNumbersCommon::checkReactionForMovingDoubleSlider;

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
