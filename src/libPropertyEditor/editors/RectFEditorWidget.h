#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class RectFEditorWidget;
}

namespace property_editor {

class RectFEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit RectFEditorWidget(QWidget* parent = nullptr);
    ~RectFEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::RectFEditorWidget> ui;
};

} // namespace property_editor
