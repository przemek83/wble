#ifndef FILTERNUMBERS_H
#define FILTERNUMBERS_H

#include <memory>

#include <QWidget>

#include "Filter.h"
#include "wble_global.h"

namespace Ui
{
class FilterNumbers;
} // namespace Ui

/**
 * @class FilterNumbers
 * @brief Numbers filter for numeric values.
 */
class WBLE_EXPORT FilterNumbers : public Filter
{
    Q_OBJECT
public:
    FilterNumbers(const QString& name,
                  double from,
                  double to,
                  QWidget* parent = nullptr);

    ~FilterNumbers() override;

    FilterNumbers& operator=(const FilterNumbers& other) = delete;
    FilterNumbers(const FilterNumbers& other) = delete;

    FilterNumbers& operator=(FilterNumbers&& other) = delete;
    FilterNumbers(FilterNumbers&& other) = delete;

    /**
     * Emitted when filter state was changed.
     * @param from Current value of from number.
     * @param to Current value of to number.
     */
Q_SIGNALS:
    void newNumericFilter(double from, double to);

protected:
    void checkedStateChanged(bool checked) override;

private:
    void initValidators();

    void initDoubleSlider();

    void initLineEdits();

    void emitChangeSignal();

    Ui::FilterNumbers* ui;

    /// Minimum set on filter creation.
    double initialFromValue_;

    /// Maximum set on filter creation.
    double initialToValue_;

    ///Numbers are doubles.
    bool doubleMode_ {false};

private Q_SLOTS:
    /**
     * Trigerred on change of left handle on slider.
     * @param newValue new value.
     */
    void sliderFromChanged(double newValue);

    /**
     * Trigerred on change of right handle on slider.
     * @param newValue new value.
     */
    void sliderToChanged(double newValue);

    /**
     * Trigerred on change of left LineEdit (from).
     */
    void fromEditingFinished();

    /**
     * Trigerred on change of right LineEdit (to).
     */
    void toEditingFinished();
};

#endif // FILTERNUMBERS_H
