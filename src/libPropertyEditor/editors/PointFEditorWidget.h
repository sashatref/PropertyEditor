#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class PointFEditorWidget;
}

namespace property_editor {

class PointFEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit PointFEditorWidget(QWidget* parent = nullptr);
    ~PointFEditorWidget();

    void SetValue(const QVariant& value) override;

private:
    std::unique_ptr<Ui::PointFEditorWidget> ui;
};

} // namespace property_editor
