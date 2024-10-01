#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class FloatEditorWidget;
}

namespace property_editor {

class FloatEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit FloatEditorWidget(QWidget* parent = nullptr);
    ~FloatEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::FloatEditorWidget> ui;
};

} // namespace property_editor
