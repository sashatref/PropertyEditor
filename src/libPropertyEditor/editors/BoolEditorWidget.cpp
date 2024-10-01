#include "BoolEditorWidget.h"
#include "ui_BoolEditorWidget.h"

namespace property_editor {

BoolEditorWidget::BoolEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::BoolEditorWidget>())
{
    ui->setupUi(this);

    connect(ui->switcher, &Switcher::ValueChanged, this, [this](bool v) {
        emit ValueChanged(QVariant(v));
    });
}

BoolEditorWidget::~BoolEditorWidget() = default;

void BoolEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->switcher);
    ui->switcher->SetValue(value.toBool());
}

} // namespace property_editor
