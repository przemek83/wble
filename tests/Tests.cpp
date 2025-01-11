#include <QStyleFactory>
#include <QTest>

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
    const QColor color(240, 240, 240);
    const QColor altColor(225, 225, 225);
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Button, color);
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Dark, altColor);
    palette.setColor(QPalette::Light, altColor);
    palette.setColor(QPalette::Midlight, altColor);
    palette.setColor(QPalette::Mid, altColor);
    palette.setColor(QPalette::Shadow, altColor);
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, altColor);
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, color);
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, altColor);
    palette.setColor(QPalette::Highlight, altColor);
    palette.setColor(QPalette::HighlightedText, Qt::white);

    QApplication::setPalette(palette);
}
}  // namespace

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);

    QStyle* style = QStyleFactory::create(QStringLiteral("Fusion"));
    QApplication::setStyle(style);
    setLightPalette();

    int status{EXIT_SUCCESS};
    DoubleSliderTest doubleSliderTest;
    status |= QTest::qExec(&doubleSliderTest);

    FilterDatesTest filterDatesTest;
    status |= QTest::qExec(&filterDatesTest);

    FilterStringsTest filterStringsTest;
    status |= QTest::qExec(&filterStringsTest);

    FilterIntegersTest filterIntegersTest;
    status |= QTest::qExec(&filterIntegersTest);

    FilterDoublesTest filterDoublesTest;
    status |= QTest::qExec(&filterDoublesTest);

    ProgressBarCounterTest progressBarCounterTest;
    status |= QTest::qExec(&progressBarCounterTest);

    ProgressBarInfiniteTest progressBarInfiniteTest;
    status |= QTest::qExec(&progressBarInfiniteTest);

    UtilitiesTest utilitiesTest;
    status |= QTest::qExec(&utilitiesTest);

    return status;
}
