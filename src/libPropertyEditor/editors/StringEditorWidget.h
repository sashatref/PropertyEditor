#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class StringEditorWidget;
}

namespace property_editor {

class StringEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit StringEditorWidget(QWidget* parent = nullptr);
    ~StringEditorWidget();

    void SetValue(const QVariant& value) override;

private slots:
    void on_edit_button_clicked();

private:
    std::unique_ptr<Ui::StringEditorWidget> ui;
};

} // namespace property_editor
