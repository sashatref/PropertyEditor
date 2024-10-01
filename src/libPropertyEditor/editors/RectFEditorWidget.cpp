#include "RectFEditorWidget.h"
#include "ui_RectFEditorWidget.h"

namespace property_editor {

RectFEditorWidget::RectFEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::RectFEditorWidget>())
{
    ui->setupUi(this);

    QList<QDoubleSpinBox*> spin_arr = {ui->spin_x, ui->spin_y, ui->spin_w, ui->spin_h};

    auto fn = [this] {
        emit ValueChanged(QVariant(QRectF{ui->spin_x->value(), ui->spin_y->value(), ui->spin_w->value(), ui->spin_h->value()}));
    };

    for (auto* it : spin_arr) {
        it->setMinimum(std::numeric_limits<float>::min());
        it->setMinimum(std::numeric_limits<float>::min());
        connect(it, qOverload<double>(&QDoubleSpinBox::valueChanged), this, fn);
    }
}

RectFEditorWidget::~RectFEditorWidget() = default;

void RectFEditorWidget::SetValue(const QVariant& value)
{
    QRectF rect = value.toRectF();

    {
        QSignalBlocker blocker(ui->spin_x);
        ui->spin_x->setValue(rect.x());
    }

    {
        QSignalBlocker blocker(ui->spin_y);
        ui->spin_y->setValue(rect.y());
    }

    {
        QSignalBlocker blocker(ui->spin_w);
        ui->spin_w->setValue(rect.width());
    }

    {
        QSignalBlocker blocker(ui->spin_h);
        ui->spin_h->setValue(rect.height());
    }
}

} // namespace property_editor
