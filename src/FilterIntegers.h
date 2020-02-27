#ifndef FILTERINTEGERS_H
#define FILTERINTEGERS_H

#include "FilterNumbers.h"

/**
 * @class FilterIntegers
 * @brief Numeric filter for integer values.
 */
class WBLE_EXPORT FilterIntegers : public FilterNumbers
{
    Q_OBJECT
public:
    FilterIntegers(const QString& name,
                   double from,
                   double to,
                   QWidget* parent = nullptr);

    ~FilterIntegers() override = default;

    FilterIntegers& operator=(const FilterIntegers& other) = delete;
    FilterIntegers(const FilterIntegers& other) = delete;

    FilterIntegers& operator=(FilterIntegers&& other) = delete;
    FilterIntegers(FilterIntegers&& other) = delete;

    /**
     * Emitted when filter state was changed.
     * @param from Current value of from number.
     * @param to Current value of to number.
     */
Q_SIGNALS:
    void newNumericFilter(int from, int to);

protected:
    bool isDoubleMode() const override;

    void emitChangeSignal() override;
};

#endif // FILTERINTEGERS_H
