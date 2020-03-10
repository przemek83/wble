#include "ProgressBar.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QTimer>

ProgressBar::ProgressBar(QString title,
                         QWidget* parent)
    : QWidget(parent),
      title_(title),
      color_(Qt::blue),
      brush_(color_)
{
    static const char newLine('\n');
    setWindowTitle(QString(title_).replace(newLine, ' '));

    if (parent == nullptr)
    {
        setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        setWindowModality(Qt::ApplicationModal);
    }

    const int defaultWidth {120};
    const int defaultHeight {140};
    setMinimumSize(defaultWidth, defaultHeight);
    const QSize size(defaultWidth, defaultHeight);
    resize(size);

    initPen();
    initCounterFont();
    initTitleFont();
    initArcRectangle();
    initTitleRectangle();

    QWidget* activeWidget = QApplication::activeWindow();
    if (activeWidget != nullptr)
    {
        move(QApplication::activeWindow()->geometry().center() -
             geometry().center());
    }
}

void ProgressBar::start()
{
    running_ = true;
}

void ProgressBar::stop()
{
    running_ = false;
}

void ProgressBar::restart()
{
    stop();
    start();
}

bool ProgressBar::isRunning()
{
    return running_;
}

void ProgressBar::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    paintProgress(painter);
    paintTitle(painter);
}

void ProgressBar::initPainter(QPainter* painter) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen_);
    painter->setBrush(brush_);
    painter->setFont(counterFont_);
}

void ProgressBar::initPen()
{
    pen_.setColor(color_);
    pen_.setWidth(LINE_WIDTH);
    pen_.setStyle(Qt::SolidLine);
}

void ProgressBar::initCounterFont()
{
    const double counterFontFactor {2.5};
    const int fontPointSizen = QApplication::font().pointSize();
    counterFont_.setPointSize(lround(fontPointSizen * counterFontFactor));
    counterFont_.setStyleStrategy(QFont::PreferAntialias);
}

void ProgressBar::initTitleFont()
{
    const int fontPointSizen = QApplication::font().pointSize();
    const double titleFontFactor {1.5};
    titleFont_.setPointSize(lround(fontPointSizen * titleFontFactor));
    titleFont_.setBold(true);
}

void ProgressBar::initArcRectangle()
{
    QSize arcSize(width() - 4 * LINE_WIDTH, width() - 4 * LINE_WIDTH);
    arcRectangle_ = QRect(width() / 2 - arcSize.width() / 2,
                          (width() - 2 * LINE_WIDTH) / 2 - arcSize.height() / 2,
                          arcSize.width(),
                          arcSize.height());
}

void ProgressBar::initTitleRectangle()
{
    titleRectangle_ = QRect(0,
                            height() - LINE_WIDTH * 4,
                            width(),
                            LINE_WIDTH * 4);
}

void ProgressBar::paintTitle(QPainter& painter)
{
    painter.setFont(titleFont_);
    painter.drawText(titleRectangle_, Qt::AlignCenter, title_);
}
