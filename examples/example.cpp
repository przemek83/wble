#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

#include "DoubleSlider.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    const int min {0};
    const int max {100};

    QWidget widget;

    QGroupBox groupBox(QStringLiteral("DoubleSlider"), &widget);
    QVBoxLayout layout(&widget);

    DoubleSlider slider(min, max, &widget);
    layout.addWidget(&slider);

    QLabel fromLabel(QString::number(min), &widget);
    const auto updateFromLabel = [&](int newMin) {fromLabel.setText(QString::number(newMin));};
    QObject::connect(&slider,
                     &DoubleSlider::minChanged,
                     &fromLabel,
                     updateFromLabel);
    layout.addWidget(&fromLabel);

    QLabel toLabel(QString::number(max), &widget);
    const auto updateToLabel = [&](int newMax) {toLabel.setText(QString::number(newMax));};
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
