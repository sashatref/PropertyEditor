#include "Switcher.h"
#include "ui_Switcher.h"

namespace property_editor {

Switcher::Switcher(QWidget* parent)
        : QWidget(parent)
        , ui(std::make_unique<Ui::Switcher>())
{
    ui->setupUi(this);

    connect(ui->on_button, &QToolButton::toggled, this, [this](bool _v) {
        QSignalBlocker blocker(ui->off_button);
        ui->off_button->setChecked(!_v);

        emit ValueChanged(GetValue());
    });
    connect(ui->off_button, &QToolButton::toggled, this, [this](bool _v) {
        QSignalBlocker blocker(ui->on_button);
        ui->on_button->setChecked(!_v);

        emit ValueChanged(GetValue());
    });
}

Switcher::~Switcher() = default;

void Switcher::SetValue(bool _v)
{
    ui->on_button->setChecked(_v);
    ui->off_button->setChecked(!_v);
}

bool Switcher::GetValue() const
{
    return ui->on_button->isChecked();
}

} // namespace property_editor
