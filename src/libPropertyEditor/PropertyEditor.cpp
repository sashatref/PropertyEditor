#include "PropertyEditor.h"
#include "ui_PropertyEditor.h"

#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QMetaProperty>

#include "editors/ArrayEditorWidget.h"
#include "editors/BoolEditorWidget.h"
#include "editors/ColorEditorWidget.h"
#include "editors/DoubleEditorWidget.h"
#include "editors/EnumEditorWidget.h"
#include "editors/FloatEditorWidget.h"
#include "editors/IntEditorWidget.h"
#include "editors/PointFEditorWidget.h"
#include "editors/RectFEditorWidget.h"
#include "editors/StringEditorWidget.h"

namespace property_editor {

namespace {
template <class Type, class Editor>
void RegisterValueEditor(PropertyEditor* editor)
{
    editor->RegisterEditor(qMetaTypeId<Type>(), [](QWidget* parent) {
        return new Editor(parent);
    });
}
}  // namespace

PropertyEditor::PropertyEditor(QWidget* parent)
        : QWidget(parent)
        , ui(std::make_shared<Ui::PropertyEditor>())
{
    ui->setupUi(this);

    RegisterValueEditor<bool, BoolEditorWidget>(this);
    RegisterValueEditor<int, IntEditorWidget>(this);
    RegisterValueEditor<float, FloatEditorWidget>(this);
    RegisterValueEditor<double, DoubleEditorWidget>(this);
    RegisterValueEditor<QString, StringEditorWidget>(this);
    RegisterValueEditor<QPointF, PointFEditorWidget>(this);
    RegisterValueEditor<QColor, ColorEditorWidget>(this);
    RegisterValueEditor<QRectF, RectFEditorWidget>(this);
}

PropertyEditor::~PropertyEditor() = default;

void PropertyEditor::BindValue(const QMetaObject *mo, void *obj)
{
    ui->tree_widget->clear();
    ProcessMetaObject(mo, obj, ui->tree_widget->invisibleRootItem());
}

void PropertyEditor::RegisterEditor(int type_id, EditorCreator editor_creator)
{
    m_value_editors[type_id] = editor_creator;
}

void PropertyEditor::RegisterArrayType(int array_id, int element_id)
{
    m_array_types[array_id] = element_id;
}

void PropertyEditor::ProcessMetaObject(const QMetaObject* mo, void* obj, QTreeWidgetItem* parent)
{
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); i++) {
        QMetaProperty mp = mo->property(i);

        QTreeWidgetItem* item = new QTreeWidgetItem();
        parent->addChild(item);
        item->setText(0, mp.name());

        EditorWidget* editor_widget = nullptr;

        auto array_type_it = m_array_types.find(mp.userType());
        if (array_type_it != m_array_types.end()) {
            editor_widget = new ArrayEditorWidget(m_value_editors, item, array_type_it->first, array_type_it->second, this);
        }
        else if (mp.isEnumType()) {
            editor_widget = new EnumEditorWidget(mp.enumerator(), this);
        }
        else {
            auto value_editor_it = m_value_editors.find(mp.userType());
            if (value_editor_it != m_value_editors.end()) {
                editor_widget = value_editor_it->second(this);
            }
        }

        if (editor_widget) {
            editor_widget->SetValue(mp.readOnGadget(obj));

            auto fn = [mp, obj, this](const QVariant& value) {
                try {
                    qDebug() << mp.writeOnGadget(obj, value);
                }
                catch (const std::exception& e) {
                    QMessageBox::warning(this, tr("Error"), e.what());
                };

                emit ValueChanged();
            };
            connect(editor_widget, &EditorWidget::ValueChanged, this, fn);
        }

        ui->tree_widget->setItemWidget(item, 1, editor_widget);
    }
}
} // namespace property_editor
