#include "PointFEditorWidget.h"
#include "ui_PointFEditorWidget.h"

namespace property_editor {

PointFEditorWidget::PointFEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::PointFEditorWidget>())
{
    ui->setupUi(this);

    ui->spin_x->setMinimum(std::numeric_limits<float>::min());
    ui->spin_y->setMinimum(std::numeric_limits<float>::min());
    ui->spin_x->setMaximum(std::numeric_limits<float>::max());
    ui->spin_y->setMaximum(std::numeric_limits<float>::max());

    auto fn = [this] {
        emit ValueChanged(QVariant(QPointF{ui->spin_x->value(), ui->spin_y->value()}));
    };
    connect(ui->spin_x, qOverload<double>(&QDoubleSpinBox::valueChanged), this, fn);
    connect(ui->spin_y, qOverload<double>(&QDoubleSpinBox::valueChanged), this, fn);
}

PointFEditorWidget::~PointFEditorWidget() = default;

void PointFEditorWidget::SetValue(const QVariant& value)
{
    QPointF point = value.toPointF();

    {
        QSignalBlocker blocker(ui->spin_x);
        ui->spin_x->setValue(point.x());
    }

    {
        QSignalBlocker blocker(ui->spin_y);
        ui->spin_y->setValue(point.y());
    }
}

} // namespace property_editor
