#pragma once

#include <QGroupBox>

#include "wble_global.h"

/// @class Filter
/// @brief Filters base class.
class WBLE_EXPORT Filter : public QGroupBox
{
    Q_OBJECT
public:
    explicit Filter(const QString& title, QWidget* parent = nullptr);

public Q_SLOTS:
    void setChecked(bool checked);

protected:
    virtual void checkedStateChanged(bool checked) = 0;
};
