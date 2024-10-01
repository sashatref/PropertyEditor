#include "ArrayEditorWidget.h"
#include "ui_ArrayEditorWidget.h"

#include <QMessageBox>

namespace property_editor {

ArrayEditorWidget::ArrayEditorWidget(
    const std::map<int, PropertyEditor::EditorCreator>& editor_creator,
    QTreeWidgetItem* parent_item,
    int arr_id,
    int element_id,
    QWidget* parent
)
        : EditorWidget(parent)
        , ui(std::make_unique<Ui::ArrayEditorWidget>())
        , m_parent_item(parent_item)
        , m_arr_id(arr_id)
        , m_element_id(element_id)
        , m_value_editors(editor_creator)
{
    ui->setupUi(this);

    connect(ui->button_add, &QPushButton::clicked, this, [this] {
        m_data << QVariant(m_element_id, nullptr);
        SetValue(m_data);
    });
}

ArrayEditorWidget::~ArrayEditorWidget() = default;

void ArrayEditorWidget::SetValue(const QVariant& value)
{
    ClearChildItems();
    m_data = value.toList();

    for (int i = 0; i < m_data.size(); i++) {
        const QVariant& v = m_data[i];
        QTreeWidgetItem* item = new QTreeWidgetItem();
        m_child_items.append(item);
        m_parent_item->addChild(item);
        item->setText(0, QString("[%1]").arg(i));
        item->treeWidget()->setItemWidget(item, 0, CreateRemoveButton(i));

        EditorWidget* editor_widget = nullptr;

        auto value_editor_it = m_value_editors.find(v.userType());
        if (value_editor_it != m_value_editors.end()) {
            editor_widget = value_editor_it->second(this);
        }

        if (editor_widget) {
            editor_widget->SetValue(v);
            connect(editor_widget, &EditorWidget::ValueChanged, this, [this, i](const QVariant& value) {
                if (i < m_data.size()) {
                    m_data[i] = value;
                }
                emit ValueChanged(m_data);
            });
        }

        m_parent_item->treeWidget()->setItemWidget(item, 1, editor_widget);
    }
    m_parent_item->setExpanded(true);
}

void ArrayEditorWidget::RemoveButtonClicked(int index)
{
    if (QMessageBox::question(this, tr("Are you sure?"), tr("Remove item: %1?").arg(index)) != QMessageBox::Yes) {
        return;
    }

    if (index < m_data.size()) {
        m_data.removeAt(index);
        SetValue(m_data);
    }
}

void ArrayEditorWidget::ClearChildItems()
{
    qDeleteAll(m_child_items);
    m_child_items.clear();
}

QWidget* ArrayEditorWidget::CreateRemoveButton(int index)
{
    QPushButton* remove_btn = new QPushButton(this);
    remove_btn->setText("X");
    connect(remove_btn, &QPushButton::clicked, this, [this, index] {
        RemoveButtonClicked(index);
    });
    return remove_btn;
}

} // namespace property_editor
