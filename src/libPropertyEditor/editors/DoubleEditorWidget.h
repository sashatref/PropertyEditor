#pragma once

#include <memory>
#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class DoubleEditorWidget;
}

namespace property_editor {

class DoubleEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit DoubleEditorWidget(QWidget* parent = nullptr);
    ~DoubleEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::DoubleEditorWidget> ui;
};

} // namespace property_editor
