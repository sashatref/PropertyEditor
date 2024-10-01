#pragma once

#include <QMainWindow>

namespace Ui {
class PropertyEditorTest;
}

class PropertyEditorTest : public QMainWindow {
    Q_OBJECT

public:
    explicit PropertyEditorTest(QWidget* parent = nullptr);
    ~PropertyEditorTest();

private:
    Ui::PropertyEditorTest* ui;
};
