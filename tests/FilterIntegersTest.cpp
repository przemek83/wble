#include "FilterIntegersTest.h"

#include <QLineEdit>
#include <QSignalSpy>
#include <QtTest/QtTest>
#include <QTest>

#include "DoubleSlider.h"
#include "FilterIntegers.h"

#include "FilterNumbersCommon.h"

using namespace FilterNumbersCommon;

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
