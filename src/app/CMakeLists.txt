
set( ASSETS
    assets/menu.ico
    assets/subtract.ico
    assets/close.ico
    assets/settings.png
    assets/history.png
    assets/angle.png
    assets/calculator.png
    assets/data.png
)

set( QML_SOURCE
    qml/main.qml
    qml/pages/Standart.qml
    qml/pages/Converter.qml
    qml/components/StyledDrawerButton.qml
    qml/components/StyledToolButton.qml
    qml/components/StyledWindowButtons.qml
    qml/components/StyledTextInput.qml
    qml/components/StyledComboItem.qml
    qml/components/StyledComboBox.qml
    qml/components/StyledDialog.qml
)

set( SOURCE
    src/main.cpp
    src/Utils.hpp
    src/OperationHistory.cpp
    src/OperationHistory.hpp
    src/Calculator.cpp
    src/Calculator.hpp
    src/Converter.cpp
    src/Converter.hpp
    src/ConverterHandler.cpp
    src/ConverterHandler.hpp
)

qt_add_executable( qalculator ${SOURCE} )

qt_add_resources( qalculator "assets"
    BASE "assets"
    PREFIX "/assets"
    FILES ${ASSETS}
)
qt_add_resources( qalculator "qml"
    BASE "qml"
    PREFIX "/qml"
    FILES ${QML_SOURCE}
)

target_link_libraries( qalculator PRIVATE Qt6::Gui Qt6::Quick )
