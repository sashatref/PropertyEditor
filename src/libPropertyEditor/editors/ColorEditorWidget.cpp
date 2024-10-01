#include "ColorEditorWidget.h"
#include "ui_ColorEditorWidget.h"

#include <QColorDialog>

namespace property_editor {

ColorEditorWidget::ColorEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::ColorEditorWidget>())
{
    ui->setupUi(this);

    connect(ui->line_edit, &QLineEdit::textChanged, this, [this](const QString& text) {
        m_color = QColor(text);
        emit ValueChanged(QVariant::fromValue(m_color));
    });
}

ColorEditorWidget::~ColorEditorWidget()
{
}

void ColorEditorWidget::SetValue(const QVariant& value)
{
    m_color = value.value<QColor>();
    ui->line_edit->setText(m_color.name());
}

void ColorEditorWidget::on_edit_button_clicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_color);
    if (dialog.exec() == QDialog::Accepted) {
        ui->line_edit->setText(dialog.currentColor().name());
    }
}

} // namespace property_editor
