
set( QML_SOURCES
    qml/style/StyledDrawerButton.qml
    qml/style/StyledToolButton.qml
    qml/style/StyledWindowButtons.qml
    qml/style/StyledTextInput.qml
    qml/style/StyledComboItem.qml
    qml/style/StyledComboBox.qml
    qml/style/StyledDialog.qml
)

set( INCLUDES
)
set( SOURCES

    ${INCLUDES}
)

qt_add_library( Qalculator.Style STATIC )

target_include_directories( Qalculator.Style
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

qt_add_qml_module( Qalculator.Style
    URI "qalculator.style"
    QML_FILES ${QML_SOURCES}
    NO_PLUGIN
)

target_link_libraries( Qalculator.Style PRIVATE Qt6::Quick )
