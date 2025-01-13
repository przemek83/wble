#pragma once

#include <QGroupBox>

#include "wble_global.h"

/// @class Filter
/// @brief Filters base class.
class WBLE_EXPORT Filter : public QGroupBox
{
    Q_OBJECT
public:
    Filter(const QString& title, QWidget* parent);
    explicit Filter(const QString& title);

public Q_SLOTS:
    void setChecked(bool checked);

protected:
    virtual void checkedStateChanged(bool checked) = 0;
};
