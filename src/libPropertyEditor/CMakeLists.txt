project(PropertyEditor)

add_library(${PROJECT_NAME} STATIC
    PropertyEditor.cpp
    PropertyEditor.h
    PropertyEditor.ui
    PropertyEditorDialog.cpp
    PropertyEditorDialog.h
    PropertyEditorDialog.ui
    editors/ArrayEditorWidget.cpp
    editors/ArrayEditorWidget.h
    editors/ArrayEditorWidget.ui
    editors/BoolEditorWidget.cpp
    editors/BoolEditorWidget.h
    editors/BoolEditorWidget.ui
    editors/ColorEditorWidget.cpp
    editors/ColorEditorWidget.h
    editors/ColorEditorWidget.ui
    editors/DoubleEditorWidget.cpp
    editors/DoubleEditorWidget.h
    editors/DoubleEditorWidget.ui
    editors/EnumEditorWidget.cpp
    editors/EnumEditorWidget.h
    editors/EnumEditorWidget.ui
    editors/FloatEditorWidget.cpp
    editors/FloatEditorWidget.h
    editors/FloatEditorWidget.ui
    editors/IntEditorWidget.cpp
    editors/IntEditorWidget.h
    editors/IntEditorWidget.ui
    editors/PointFEditorWidget.cpp
    editors/PointFEditorWidget.h
    editors/PointFEditorWidget.ui
    editors/RectFEditorWidget.cpp
    editors/RectFEditorWidget.h
    editors/RectFEditorWidget.ui
    editors/StringEditorWidget.cpp
    editors/StringEditorWidget.h
    editors/StringEditorWidget.ui
    editors/Switcher.cpp
    editors/Switcher.h
    editors/Switcher.ui
    editors/StringEditorDialog.h
    editors/StringEditorDialog.cpp
    editors/StringEditorDialog.ui
)
target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Qt5::Core Qt5::Widgets
)
