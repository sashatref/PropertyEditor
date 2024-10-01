#include "IntEditorWidget.h"
#include "ui_IntEditorWidget.h"

namespace property_editor {

IntEditorWidget::IntEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::IntEditorWidget>())
{
    ui->setupUi(this);

    ui->spinBox->setMaximum(std::numeric_limits<int>::max());
    ui->spinBox->setMinimum(std::numeric_limits<int>::min());

    connect(ui->spinBox, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        emit ValueChanged(QVariant(v));
    });
}

IntEditorWidget::~IntEditorWidget() = default;

void IntEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->spinBox);
    ui->spinBox->setValue(value.toInt());
}

} // namespace property_editor
