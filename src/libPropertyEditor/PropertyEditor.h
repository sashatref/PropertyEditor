#pragma once

#include <QTreeWidgetItem>
#include <QWidget>

namespace Ui {
class PropertyEditor;
}

namespace property_editor {

class EditorWidget : public QWidget {
    Q_OBJECT
public:
    using QWidget::QWidget;
    virtual void SetValue(const QVariant& value) = 0;

signals:
    void ValueChanged(const QVariant &new_value);
};

class PropertyEditor : public QWidget
{
    Q_OBJECT
public:
    using EditorCreator = std::function<EditorWidget*(QWidget*)>;

    explicit PropertyEditor(QWidget *parent = nullptr);
    ~PropertyEditor();

    void BindValue(const QMetaObject *mo, void *obj);
    void RegisterEditor(int type_id, EditorCreator editor_creator);
    void RegisterArrayType(int array_id, int element_id);

signals:
    void ValueChanged();

private:
    void ProcessMetaObject(const QMetaObject* mo, void* obj, QTreeWidgetItem* parent);

    std::shared_ptr<Ui::PropertyEditor> ui;
    std::map<int, EditorCreator> m_value_editors;
    std::map<int, int> m_array_types;
};

} // namespace property_editor
