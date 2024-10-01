#pragma once

#include <QDialog>

namespace Ui {
class StringEditorDialog;
}

namespace property_editor {

class StringEditorDialog : public QDialog {
    Q_OBJECT

public:
    explicit StringEditorDialog(QWidget* parent = nullptr);
    ~StringEditorDialog();

    void SetText(const QString& text);
    QString GetText() const;

private:
    std::unique_ptr<Ui::StringEditorDialog> ui;
};

} // namespace property_editor
