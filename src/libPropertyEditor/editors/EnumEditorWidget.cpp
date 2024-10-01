#include "EnumEditorWidget.h"
#include <QMetaEnum>
#include "ui_EnumEditorWidget.h"

namespace property_editor {

EnumEditorWidget::EnumEditorWidget(const QMetaEnum& me, QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::EnumEditorWidget>())
{
    ui->setupUi(this);

    connect(ui->combo_box, &QComboBox::currentTextChanged, this, [this] {
        emit ValueChanged(ui->combo_box->currentData().toInt());
    });

    for (int i = 0; i < me.keyCount(); i++) {
        ui->combo_box->addItem(me.key(i), me.value(i));
    }
}

EnumEditorWidget::~EnumEditorWidget() = default;

void EnumEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->combo_box);
    const int num = value.toInt();
    for (int i = 0; i < ui->combo_box->count(); i++) {
        if (ui->combo_box->itemData(i).toInt() == num) {
            ui->combo_box->setCurrentIndex(i);
            break;
        }
    }
}

} // namespace property_editor
