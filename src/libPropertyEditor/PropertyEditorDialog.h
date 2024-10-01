#pragma once

#include <QDialog>
#include "PropertyEditor.h"

namespace Ui {
class PropertyEditorDialog;
}

namespace property_editor {

class PropertyEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PropertyEditorDialog(QWidget *parent = nullptr);
    ~PropertyEditorDialog();

    template<class Type>
    void SetValue(const Type &v)
    {
        std::shared_ptr<DataHolder<Type>> holder = std::make_shared<DataHolder<Type>>(v);
        m_data_holder = holder;
        BindValue(&Type::staticMetaObject, &holder->data);
    }

    template<class Type>
    Type GetValue() const
    {
        if (!m_data_holder || m_data_holder->type_id != qMetaTypeId<Type>()) {
            return Type{};
        }

        std::shared_ptr<DataHolder<Type>> holder = std::dynamic_pointer_cast<DataHolder<Type>>(
            m_data_holder);
        return holder->data;
    }

    template <class Type, class Editor>
    void RegisterEditor()
    {
        RegisterEditor(qMetaTypeId<Type>(), [](QWidget* parent) {
            return new Editor(parent);
        });
    }

    void RegisterEditor(int type_id, PropertyEditor::EditorCreator editor_creator);

    template <class Type>
    void RegisterArrayType(const std::vector<Type>& = {})
    {
        RegisterArrayType(qMetaTypeId<std::vector<Type>>(), qMetaTypeId<Type>());

        if (!QMetaType::hasRegisteredConverterFunction<std::vector<Type>, QVariantList>()) {
            QMetaType::registerConverter<std::vector<Type>, QVariantList>([](const std::vector<Type>& in) {
                QVariantList out;

                for (const auto& it : in) {
                    out.push_back(QVariant::fromValue(it));
                }
                return out;
            });
        }

        if (!QMetaType::hasRegisteredConverterFunction<QVariantList, std::vector<Type>>()) {
            QMetaType::registerConverter<QVariantList, std::vector<Type>>([](const QVariantList& in) {
                std::vector<Type> out;

                for (const auto& it : in) {
                    out.push_back(it.value<Type>());
                }
                return out;
            });
        }
    }

    void RegisterArrayType(int array_id, int element_id);

private slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

private:
    class DataHolderBase
    {
    public:
        DataHolderBase(int id)
            : type_id(id)
        {}

        virtual ~DataHolderBase() = default;
        int type_id{};
    };

    template<class Type>
    class DataHolder : public DataHolderBase
    {
    public:
        DataHolder(const Type &v)
            : DataHolderBase(qMetaTypeId<Type>())
            , data(v)
        {}

        Type data;
    };

    void BindValue(const QMetaObject *mo, void *obj);

    Ui::PropertyEditorDialog *ui;
    std::shared_ptr<DataHolderBase> m_data_holder;
};

} // namespace property_editor
