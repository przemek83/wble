#include "ProgressBar.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QTimer>

ProgressBar::ProgressBar(QString title,
                         int max,
                         QWidget* parent)
    : QWidget(parent),
      maxValue_(max),
      title_(title)
{
    static const char newLine('\n');
    setWindowTitle(QString(title_).replace(newLine, ' '));

    if (nullptr == parent)
    {
        setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        setWindowModality(Qt::ApplicationModal);
    }

    //Counter without %.
    if (0 == maxValue_)
    {
        startTimer(TIMER_DEFAULT_INTERVAL);
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

void ProgressBar::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen_);
    painter.setBrush(brush_);
    painter.setFont(counterFont_);

    constexpr int fullDegree {16};
    constexpr double hundredthOfFullCircle {3.6};
    constexpr int quarterCircleAngle {90};
    constexpr int halfCircleAngle {2 * quarterCircleAngle};

    //Counter without %.
    if (maxValue_ == 0)
    {
        const int step {45};
        int startAngle = lround(currentPercent_ * hundredthOfFullCircle * fullDegree);
        const int spanAngle = -step * fullDegree;
        painter.drawArc(arcRectangle_, startAngle, spanAngle);
        startAngle = lround((halfCircleAngle + currentPercent_ * hundredthOfFullCircle) * fullDegree);
        painter.drawArc(arcRectangle_, startAngle, spanAngle);
    }
    else
    {
        constexpr int startAngle {quarterCircleAngle * fullDegree};
        const int spanAngle = lround(-currentPercent_ * hundredthOfFullCircle * fullDegree);
        painter.drawArc(arcRectangle_, startAngle, spanAngle);
        painter.drawText(arcRectangle_,
                         Qt::AlignCenter,
                         QString::number(currentPercent_, 'f', 0) + "%");

    }

    painter.setFont(titleFont_);

    painter.drawText(titleRectangle_, Qt::AlignCenter, title_ + "...");

    if (maxValue_ != 0)
    {
        setWindowTitle(QString::number(currentPercent_) + "% " +
                       QString(title_).replace('\n', ' ') + "...");

    }
}

void ProgressBar::updateProgress(int newValue)
{
    int newPercent = lround(newValue * 1.0 / maxValue_ * 100);
    if (newPercent > currentPercent_)
    {
        currentPercent_ = newPercent;
        update();
        QApplication::processEvents();
    }
}

void ProgressBar::timerEvent(QTimerEvent* /*event*/)
{
    constexpr int maxPercent {100};
    currentPercent_++;
    currentPercent_ %= maxPercent;
    update();
}
