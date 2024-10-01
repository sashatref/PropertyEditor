#include "FloatEditorWidget.h"
#include "ui_FloatEditorWidget.h"

namespace property_editor {

FloatEditorWidget::FloatEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::FloatEditorWidget>())
{
    ui->setupUi(this);

    ui->doubleSpinBox->setMaximum(std::numeric_limits<float>::max());
    ui->doubleSpinBox->setMinimum(std::numeric_limits<float>::min());

    connect(ui->doubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [this](double v) {
        emit ValueChanged(QVariant(static_cast<float>(v)));
    });
}

void FloatEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->doubleSpinBox);
    ui->doubleSpinBox->setValue(value.toFloat());
}

FloatEditorWidget::~FloatEditorWidget() = default;

} // namespace property_editor
