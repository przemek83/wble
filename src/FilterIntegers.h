#pragma once

#include "FilterNumbers.h"

/**
 * @class FilterIntegers
 * @brief Numeric filter for integer values.
 */
class WBLE_EXPORT FilterIntegers : public FilterNumbers
{
    Q_OBJECT
public:
    FilterIntegers(const QString& name, double from, double to,
                   QWidget* parent = nullptr);

Q_SIGNALS:
    /**
     * Emitted when filter state was changed.
     * @param from Current value of from number.
     * @param to Current value of to number.
     */
    void newNumericFilter(int from, int to);

protected:
    bool isDoubleMode() const override;

    void emitChangeSignal() override;
};
