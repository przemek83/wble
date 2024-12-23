#include <QTest>
#include <QStyleFactory>

#include "DoubleSliderTest.h"
#include "FilterDatesTest.h"
#include "FilterDoublesTest.h"
#include "FilterIntegersTest.h"
#include "FilterStringsTest.h"
#include "ProgressBarCounterTest.h"
#include "ProgressBarInfiniteTest.h"
#include "UtilitiesTest.h"

namespace
{
void setLightPalette()
{
    QPalette palette;
    QColor color(240, 240, 240);
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Button, color);
    QApplication::setPalette(palette);
}
}  // namespace

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QStyle *style = QStyleFactory::create("Fusion");
    QApplication::setStyle(style);
    setLightPalette();

    DoubleSliderTest doubleSliderTest;
    QTest::qExec(&doubleSliderTest);

    FilterDatesTest filterDatesTest;
    QTest::qExec(&filterDatesTest);

    FilterStringsTest filterStringsTest;
    QTest::qExec(&filterStringsTest);

    FilterIntegersTest filterIntegersTest;
    QTest::qExec(&filterIntegersTest);

    FilterDoublesTest filterDoublesTest;
    QTest::qExec(&filterDoublesTest);

    ProgressBarCounterTest progressBarCounterTest;
    QTest::qExec(&progressBarCounterTest);

    ProgressBarInfiniteTest progressBarInfiniteTest;
    QTest::qExec(&progressBarInfiniteTest);

    UtilitiesTest utilitiesTest;
    QTest::qExec(&utilitiesTest);

    return 0;
}
