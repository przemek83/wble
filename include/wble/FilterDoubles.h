#pragma once

#include <QDoubleValidator>

#include "FilterNumbers.h"

/**
 * @class FilterDoubles
 * @brief Numeric filter for double values.
 */
class WBLE_EXPORT FilterDoubles : public FilterNumbers
{
    Q_OBJECT
public:
    FilterDoubles(const QString& name, double from, double to,
                  QWidget* parent = nullptr);

Q_SIGNALS:
    /**
     * Emitted when filter state was changed.
     * @param from Current value of from number.
     * @param to Current value of to number.
     */
    void newNumericFilter(double from, double to);

protected:
    bool isDoubleMode() const override;

    void emitChangeSignal() override;

private:
    QDoubleValidator fromValidator_;
    QDoubleValidator toValidator_;
};
