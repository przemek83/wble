#pragma once

#include <memory>

#include <QWidget>

#include "DoubleSlider.h"
#include "Filter.h"
#include "wble_global.h"

namespace Ui
{
class FilterNumbers;
}  // namespace Ui

class QLineEdit;

/**
 * @class FilterNumbers
 * @brief Base class for numeric filters.
 */
class WBLE_EXPORT FilterNumbers : public Filter
{
    Q_OBJECT
public:
    FilterNumbers(const QString& name, double from, double to,
                  QWidget* parent = nullptr);

    ~FilterNumbers() override;

protected:
    void checkedStateChanged(bool checked) override;

    virtual bool isDoubleMode() const = 0;

    virtual void emitChangeSignal() = 0;

    QLineEdit* getFromLineEdit() const;

    QLineEdit* getToLineEdit() const;

    void changeEvent(QEvent* event) override;

    const int decimalPlaces_{2};

private:
    void initDoubleSlider();

    void initLineEdits() const;

    void initColorForLineEdits();

    std::unique_ptr<Ui::FilterNumbers> ui_;

    /// Minimum set on filter creation.
    double initialFromValue_;

    /// Maximum set on filter creation.
    double initialToValue_;

    QColor defaultBackgroundColor_;

    QColor altBackgroundColor_;

    DoubleSlider doubleSlider_;

private Q_SLOTS:
    /**
     * Triggered on change of left handle on slider.
     * @param newValue new value.
     */
    void sliderFromChanged(double newValue);

    /**
     * Triggered on change of right handle on slider.
     * @param newValue new value.
     */
    void sliderToChanged(double newValue);

    /**
     * Triggered on change of left LineEdit (from).
     */
    void fromEditingFinished();

    /**
     * Triggered on change of right LineEdit (to).
     */
    void toEditingFinished();

    void lineEditContentModified(const QString& currentContent) const;
};
