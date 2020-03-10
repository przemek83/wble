#include "ProgressBar.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QTimer>

ProgressBar::ProgressBar(QString title,
                         QWidget* parent)
    : QWidget(parent),
      title_(title)
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
    const QSize size(defaultWidth, defaultHeight);
    resize(size);

    const QColor blueColor(Qt::blue);
    brush_ = QBrush(blueColor);

    pen_.setColor(blueColor);
    pen_.setWidth(LINE_WIDTH);
    pen_.setStyle(Qt::SolidLine);

    const double counterFontFactor {2.5};
    int fontPointSizen = QApplication::font().pointSize();
    counterFont_.setPointSize(lround(fontPointSizen * counterFontFactor));
    counterFont_.setStyleStrategy(QFont::PreferAntialias);
    const double titleFontFactor {1.5};
    titleFont_.setPointSize(lround(fontPointSizen * titleFontFactor));
    titleFont_.setBold(true);

    QSize arcSize(width() - 4 * LINE_WIDTH, width() - 4 * LINE_WIDTH);
    arcRectangle_ = QRect(width() / 2 - arcSize.width() / 2,
                          (width() - 2 * LINE_WIDTH) / 2 - arcSize.height() / 2,
                          arcSize.width(),
                          arcSize.height());

    titleRectangle_ = QRect(0,
                            height() - LINE_WIDTH * 4,
                            width(),
                            LINE_WIDTH * 4);

    QWidget* activeWidget = QApplication::activeWindow();
    if (nullptr != activeWidget)
    {
        move(QApplication::activeWindow()->geometry().center() -
             geometry().center());
    }
    setMinimumSize(defaultWidth, defaultHeight);
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

void  ProgressBar::paintEvent([[maybe_unused]] QPaintEvent* event)
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

void ProgressBar::paintTitle(QPainter& painter)
{
    painter.setFont(titleFont_);
    painter.drawText(titleRectangle_, Qt::AlignCenter, title_);
}
