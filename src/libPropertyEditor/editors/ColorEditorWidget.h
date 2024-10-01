#pragma once

#include <QWidget>
#include "PropertyEditor.h"

namespace Ui {
class ColorEditorWidget;
}

namespace property_editor {

class ColorEditorWidget : public EditorWidget {
    Q_OBJECT

public:
    explicit ColorEditorWidget(QWidget* parent = nullptr);
    ~ColorEditorWidget();

    void SetValue(const QVariant& value) override;

private slots:
    void on_edit_button_clicked();

private:
    std::unique_ptr<Ui::ColorEditorWidget> ui;
    QColor m_color;
};

} // namespace property_editor
