#include <QApplication>
#include <QDebug>
#include <vector>
#include "PropertyEditor.h"
#include "PropertyEditorDialog.h"

struct NestedStruct {
    Q_GADGET

    Q_PROPERTY(int val1 MEMBER val1)
    Q_PROPERTY(QString val2 MEMBER val2)
public:
    int val1{};
    QString val2;

    bool operator==(const NestedStruct& v) const
    {
        return val1 == v.val1 && val2 == v.val2;
    }

    bool operator!=(const NestedStruct& v) const
    {
        return !(*this == v);
    }
};

struct MyClass {
    enum MyEnum { Enum1, Enum2, Enum3 };
    Q_ENUM(MyEnum)
    Q_GADGET

    Q_PROPERTY(std::vector<QPointF> val11 MEMBER val11)
    Q_PROPERTY(NestedStruct val9 MEMBER val9)
    Q_PROPERTY(int val1 MEMBER val1)
    Q_PROPERTY(QString val2 MEMBER val2)
    Q_PROPERTY(double val3 MEMBER val3)
    Q_PROPERTY(float val4 MEMBER val4)
    Q_PROPERTY(QColor val5 MEMBER val5)
    Q_PROPERTY(QRectF val6 MEMBER val6)
    Q_PROPERTY(QPointF val7 MEMBER val7)
    Q_PROPERTY(bool val8 MEMBER val8)
    Q_PROPERTY(MyEnum val10 MEMBER val10)

public:
    int val1{};
    QString val2;
    double val3{};
    float val4{};
    QColor val5;
    QRectF val6;
    QPointF val7;
    bool val8{};
    NestedStruct val9{};
    MyEnum val10 = Enum2;
    std::vector<QPointF> val11;
};

QDebug operator<<(QDebug debug, const std::vector<QPointF>& vec)
{
    if (vec.empty()) {
        debug << "Empty";
    }

    for (auto& it : vec) {
        debug << it << ",";
    }
    return debug;
}

Q_DECLARE_METATYPE(NestedStruct);
Q_DECLARE_METATYPE(std::vector<QPointF>)

QString toString(const NestedStruct& v)
{
    return QString("%1 - %2").arg(v.val1).arg(v.val2);
}

QString toString(const std::vector<QPointF>& in)
{
    QStringList out;

    for (const auto& it : in) {
        out << QString("QPointF(%1, %2)").arg(it.x()).arg(it.y());
    }

    return out.join(",");
}

QString toString(const MyClass& v)
{
    return QString("%1 - %2 - [%3] - [%4] - [%5]").arg(v.val1).arg(v.val2).arg(toString(v.val9)).arg(v.val10).arg(toString(v.val11));
}

int main(int argc, char *argv[])
{
    using namespace property_editor;

    QApplication a(argc, argv);

    MyClass v;
    v.val11 = {QPointF{0, 1}, QPointF{2, 3}};

    PropertyEditorDialog dialog;
    dialog.RegisterArrayType(std::vector<QPointF>{});
    dialog.SetValue(v);

    if (dialog.exec()) {
    }

    qDebug() << toString(dialog.GetValue<MyClass>());

    return 0;
}

#include "main.moc"
