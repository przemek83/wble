#include <wble/Filter.h>

Filter::Filter(const QString& title, QWidget* parent) : QGroupBox(title, parent)
{
    connect(this, &Filter::toggled, this, &Filter::setChecked);
}

void Filter::setChecked(bool checked)
{
    QGroupBox::setChecked(checked);
    checkedStateChanged(checked);
}
