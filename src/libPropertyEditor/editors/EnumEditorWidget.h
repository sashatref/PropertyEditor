#pragma once

#include <QWidget>

#include "PropertyEditor.h"

namespace Ui {
class EnumEditorWidget;
}

namespace property_editor {

class EnumEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit EnumEditorWidget(const QMetaEnum& me, QWidget* parent = nullptr);
    ~EnumEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::EnumEditorWidget> ui;
};

} // namespace property_editor
