#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWindow>

#include "DoubleSlider.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    const double min {-100.};
    const double max {100.};

    QWidget widget;

    QGroupBox groupBox(QStringLiteral("DoubleSlider integers"), &widget);
    QVBoxLayout layout(&widget);

    DoubleSlider slider(min, max, &widget);
    layout.addWidget(&slider);

    QLabel fromLabel(QString::number(min), &widget);
    const auto updateFromLabel = [&](double newMin) {fromLabel.setText(QString::number(newMin));};
    QObject::connect(&slider,
                     &DoubleSlider::minChanged,
                     &fromLabel,
                     updateFromLabel);
    layout.addWidget(&fromLabel);

    QLabel toLabel(QString::number(max), &widget);
    const auto updateToLabel = [&](double newMax) {toLabel.setText(QString::number(newMax));};
    QObject::connect(&slider,
                     &DoubleSlider::maxChanged,
                     &toLabel,
                     updateToLabel);
    layout.addWidget(&toLabel);

    QPushButton resetButton(QStringLiteral("Reset"), &widget);
    const auto resetDoubleSlider = [&]() {slider.setCurrentMin(min); slider.setCurrentMax(max);};
    QObject::connect(&resetButton,
                     &QPushButton::clicked,
                     &slider,
                     resetDoubleSlider);
    layout.addWidget(&resetButton);

    groupBox.setLayout(&layout);

    QVBoxLayout widgetLayout(&widget);
    widgetLayout.addWidget(&groupBox);
    widgetLayout.addStretch();
    widget.setLayout(&widgetLayout);
    widget.show();

    return QApplication::exec();
}
