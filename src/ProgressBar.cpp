#include "ProgressBar.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QTimer>

ProgressBar::ProgressBar(QString title,
                         QWidget* parent)
    : QWidget(parent),
      title_(std::move(title)),
      color_(Qt::blue),
      brush_(color_)
{
    setWindowTitle(title_);

    initSizes();
    initPen();
    initCounterFont();
    initTitleFont();
    initArcRectangle();
    initTitleRectangle();
}

void ProgressBar::start()
{
    running_ = true;
}

void ProgressBar::stop()
{
    running_ = false;
}

void ProgressBar::reset()
{
    if (isRunning())
        stop();
    update();
}

bool ProgressBar::isRunning()
{
    return running_;
}

void ProgressBar::showDetached()
{
    if (parent() != nullptr)
        return;

    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);

    const QWidget* activeWidget = QApplication::activeWindow();
    if (activeWidget != nullptr)
    {
        move(QApplication::activeWindow()->geometry().center() -
             geometry().center());
    }
    show();
}

void ProgressBar::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    paintProgressBar(painter);
    paintTitle(painter);
}

void ProgressBar::initPainter(QPainter* painter) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen_);
    painter->setBrush(brush_);
    painter->setFont(counterFont_);
}

void ProgressBar::initSizes()
{
    const QSize sizeToUse(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setMinimumSize(sizeToUse);
    resize(sizeToUse);
}

void ProgressBar::initPen()
{
    pen_.setColor(color_);
    pen_.setWidth(LINE_WIDTH);
    pen_.setStyle(Qt::SolidLine);
}

void ProgressBar::initCounterFont()
{
    const int fontPointSizen = QApplication::font().pointSize();
    counterFont_.setPointSize(lround(fontPointSizen * COUNTER_FONT_FACTOR));
    counterFont_.setStyleStrategy(QFont::PreferAntialias);
}

void ProgressBar::initTitleFont()
{
    const int fontPointSize = QApplication::font().pointSize();
    titleFont_.setPointSize(lround(fontPointSize * TITLE_FONT_FACTOR));
    titleFont_.setBold(true);
}

void ProgressBar::initArcRectangle()
{
    const int arcSquareLength = width() - TITLE_HEIGHT;
    const int centerOfWidth = width() / 2;
    const int centerOfArcWidth = arcSquareLength / 2;
    arcRectangle_ = QRect(centerOfWidth - centerOfArcWidth,
                          centerOfWidth - centerOfArcWidth,
                          arcSquareLength,
                          arcSquareLength);
}

void ProgressBar::initTitleRectangle()
{
    titleRectangle_ = QRect(0,
                            height() - TITLE_HEIGHT,
                            width(),
                            TITLE_HEIGHT);
}

void ProgressBar::paintTitle(QPainter& painter)
{
    painter.setFont(titleFont_);
    painter.drawText(titleRectangle_, Qt::AlignCenter, title_);
}
