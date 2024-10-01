#pragma once

#include <QWidget>

namespace Ui {
class Switcher;
}

namespace property_editor {

class Switcher : public QWidget {
    Q_OBJECT
public:
    explicit Switcher(QWidget *parent = nullptr);
    ~Switcher();

    void SetValue(bool _v);

    bool GetValue() const;

signals:
    void ValueChanged(bool _v);

private:
    std::unique_ptr<Ui::Switcher> ui;
};

} // namespace property_editor
