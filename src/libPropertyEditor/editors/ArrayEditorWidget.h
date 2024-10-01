#pragma once

#include <QWidget>

#include "PropertyEditor.h"

namespace Ui {
class ArrayEditorWidget;
}

namespace property_editor {

class ArrayEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit ArrayEditorWidget(
        const std::map<int, PropertyEditor::EditorCreator>& editor_creator,
        QTreeWidgetItem* parent_item,
        int arr_id,
        int element_id,
        QWidget* parent = nullptr
    );
    ~ArrayEditorWidget();

    void SetValue(const QVariant& value) override;

private slots:
    void RemoveButtonClicked(int index);

private:
    QWidget* CreateRemoveButton(int index);

    void ClearChildItems();

    std::unique_ptr<Ui::ArrayEditorWidget> ui;

    QTreeWidgetItem* m_parent_item;
    QList<QTreeWidgetItem*> m_child_items;
    int m_arr_id;
    int m_element_id;

    std::map<int, PropertyEditor::EditorCreator> m_value_editors;
    QVariantList m_data;
};

} // namespace property_editor
