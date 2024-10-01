#include "PropertyEditorDialog.h"
#include "ui_PropertyEditorDialog.h"

namespace property_editor {

PropertyEditorDialog::PropertyEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PropertyEditorDialog())
{
    ui->setupUi(this);
}

PropertyEditorDialog::~PropertyEditorDialog() {}

void PropertyEditorDialog::RegisterEditor(int type_id, PropertyEditor::EditorCreator editor_creator)
{
    ui->property_editor->RegisterEditor(type_id, editor_creator);
}

void PropertyEditorDialog::RegisterArrayType(int array_id, int element_id)
{
    ui->property_editor->RegisterArrayType(array_id, element_id);
}

void PropertyEditorDialog::on_btn_ok_clicked()
{
    accept();
}

void PropertyEditorDialog::on_btn_cancel_clicked()
{
    reject();
}

void PropertyEditorDialog::BindValue(const QMetaObject *mo, void *obj)
{
    ui->property_editor->BindValue(mo, obj);
}

} // namespace property_editor
