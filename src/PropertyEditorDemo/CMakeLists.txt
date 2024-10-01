project(PropertyEditorDemo LANGUAGES CXX)

set(PROJECT_SOURCES
    main.cpp
    PropertyEditorTest.h
    PropertyEditorTest.cpp
    PropertyEditorTest.ui
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets PropertyEditor)

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
