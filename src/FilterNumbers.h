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

class QLineEdit;

/**
 * @class FilterNumbers
 * @brief Base class for numeric filters.
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

protected:
    void checkedStateChanged(bool checked) override;

    virtual bool isDoubleMode() const = 0;

    virtual void emitChangeSignal() = 0;

    QLineEdit* getFromLineEdit() const;

    QLineEdit* getToLineEdit() const;

    void changeEvent(QEvent* event) override;

private:
    void initDoubleSlider();

    void initLineEdits();

    void initColorForLineEdits();

    Ui::FilterNumbers* ui;

    /// Minimum set on filter creation.
    double initialFromValue_;

    /// Maximum set on filter creation.
    double initialToValue_;

    QColor defaultBackgroundColor_;

    QColor altBackgroundColor_;

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

    void lineEditContentModified(const QString& currentContent);
};

#endif // FILTERNUMBERS_H
