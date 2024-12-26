#include <QApplication>
#include <QStyleFactory>

#include "Examples.h"

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    Examples examples;
    examples.show();

    return QApplication::exec();
}
