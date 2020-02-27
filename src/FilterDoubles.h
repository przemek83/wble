#ifndef FILTERDOUBLES_H
#define FILTERDOUBLES_H

#include "FilterNumbers.h"

/**
 * @class FilterDoubles
 * @brief Numeric filter for double values.
 */
class WBLE_EXPORT FilterDoubles : public FilterNumbers
{
    Q_OBJECT
public:
    FilterDoubles(const QString& name,
                  double from,
                  double to,
                  QWidget* parent = nullptr);

    ~FilterDoubles() override = default;

    FilterDoubles& operator=(const FilterDoubles& other) = delete;
    FilterDoubles(const FilterDoubles& other) = delete;

    FilterDoubles& operator=(FilterDoubles&& other) = delete;
    FilterDoubles(FilterDoubles&& other) = delete;

    /**
     * Emitted when filter state was changed.
     * @param from Current value of from number.
     * @param to Current value of to number.
     */
Q_SIGNALS:
    void newNumericFilter(double from, double to);

protected:
    bool isDoubleMode() const override;

    void emitChangeSignal() override;
};

#endif // FILTERDOUBLES_H
