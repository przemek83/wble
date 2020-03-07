#ifndef FILTERINTEGERSTEST_H
#define FILTERINTEGERSTEST_H

#include <QList>
#include <QObject>

class QLineEdit;

class FilterIntegersTest: public QObject
{
    Q_OBJECT
private slots:
    void testToggling();

    void testChangingEditLinesValues();

private:
    std::tuple<QLineEdit*, QLineEdit*> getLineEdits(QList<QLineEdit*> lineEdits) const;

    static constexpr int fromValue_ {0};
    static constexpr int toValue_ {100};

    static constexpr int NO_SIGNAL {0};
    static constexpr int SIGNAL_RECEIVED {1};
};

#endif // FILTERINTEGERSTEST_H
