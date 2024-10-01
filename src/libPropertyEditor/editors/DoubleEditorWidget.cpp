#include "DoubleEditorWidget.h"
#include "ui_DoubleEditorWidget.h"

namespace property_editor {

DoubleEditorWidget::DoubleEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::DoubleEditorWidget>())
{
    ui->setupUi(this);

    ui->doubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox->setMinimum(std::numeric_limits<double>::min());

    connect(ui->doubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        emit ValueChanged(QVariant(v));
    });
}

DoubleEditorWidget::~DoubleEditorWidget() = default;

void DoubleEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->doubleSpinBox);
    ui->doubleSpinBox->setValue(value.toDouble());
}

} // namespace property_editor
