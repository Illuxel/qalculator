
set( QML_SOURCES
    qml/StyledDrawerButton.qml
    qml/StyledToolButton.qml
    qml/StyledWindowButtons.qml
    qml/StyledTextInput.qml
    qml/StyledComboItem.qml
    qml/StyledComboBox.qml
    qml/StyledDialog.qml
)

set( INCLUDES
)
set( SOURCES

    ${INCLUDES}
)

qt_add_qml_module( Qalculator.Style STATIC
    URI "qalculator.style"
    QML_FILES ${QML_SOURCES}
    NO_PLUGIN
)

target_link_libraries( Qalculator.Style PRIVATE Qt6::Quick )
