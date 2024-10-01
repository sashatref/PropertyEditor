#include "StringEditorDialog.h"
#include "ui_StringEditorDialog.h"

namespace property_editor {

StringEditorDialog::StringEditorDialog(QWidget* parent)
        : QDialog(parent)
        , ui(std::make_unique<Ui::StringEditorDialog>())
{
    ui->setupUi(this);
}

StringEditorDialog::~StringEditorDialog() = default;

void StringEditorDialog::SetText(const QString& text)
{
    ui->plain_text_edit->setPlainText(text);
}

QString StringEditorDialog::GetText() const
{
    return ui->plain_text_edit->toPlainText();
}

} // namespace property_editor
