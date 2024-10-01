#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class IntEditorWidget;
}

namespace property_editor {

class IntEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit IntEditorWidget(QWidget* parent = nullptr);
    ~IntEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::IntEditorWidget> ui;
};

} // namespace property_editor
