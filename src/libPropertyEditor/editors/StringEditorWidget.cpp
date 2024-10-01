#include "StringEditorWidget.h"
#include "ui_StringEditorWidget.h"

#include "StringEditorDialog.h"

namespace property_editor {

StringEditorWidget::StringEditorWidget(QWidget* parent)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::StringEditorWidget>())
{
    ui->setupUi(this);

    connect(ui->line_edit, &QLineEdit::textChanged, this, [this](const QString& text) {
        emit ValueChanged(QVariant(text));
    });
}

StringEditorWidget::~StringEditorWidget() = default;

void StringEditorWidget::SetValue(const QVariant& value)
{
    QSignalBlocker blocker(ui->line_edit);
    ui->line_edit->setText(value.toString());
}

void StringEditorWidget::on_edit_button_clicked()
{
    StringEditorDialog dialog(this);
    dialog.setWindowTitle(tr("String Editor"));
    dialog.SetText(ui->line_edit->text());
    if (dialog.GetText() == QDialog::Accepted) {
        ui->line_edit->setText(dialog.GetText());
    }
}
} // namespace property_editor
