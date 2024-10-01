#pragma once

#include <QWidget>

#include "PropertyEditor.h"

namespace Ui {
class BoolEditorWidget;
}

namespace property_editor {

class BoolEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit BoolEditorWidget(QWidget* parent = nullptr);
    ~BoolEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::BoolEditorWidget> ui;
};

} // namespace property_editor
