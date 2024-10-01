#include "PropertyEditorTest.h"
#include "ui_PropertyEditorTest.h"

PropertyEditorTest::PropertyEditorTest(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::PropertyEditorTest)
{
    ui->setupUi(this);
}

PropertyEditorTest::~PropertyEditorTest()
{
    delete ui;
}
