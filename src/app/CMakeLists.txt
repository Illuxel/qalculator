
set( ASSETS
    assets/icons/icon_menu.png
    assets/icons/icon_subtract.png
    assets/icons/icon_close.png
    assets/icons/icon_settings.png
    assets/icons/icon_history.png
    assets/icons/icon_angle.png
    assets/icons/icon_calculator.png
    assets/icons/icon_data.png
)

set( QML_SOURCES
    qml/page/Converter.qml
    qml/page/Calculator.qml
    qml/MainWindow.qml
)

set( INCLUDES
    src/Utils.hpp
    src/OperationHistory.hpp
    src/Calculator.hpp
    src/Converter.hpp
    src/ConverterHandler.hpp
)

set( SOURCES

    ${INCLUDES}

    src/main.cpp
    src/OperationHistory.cpp
    src/Calculator.cpp
    src/Converter.cpp
    src/ConverterHandler.cpp
)

qt_add_executable( Qalculator.App MANUAL_FINALIZATION ${SOURCES} )

add_subdirectory( platforms )

qt_finalize_executable( Qalculator.App )

target_include_directories( Qalculator.App
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

qt_add_resources( Qalculator.App "app_assets"
    BASE "assets/icons"
    PREFIX "/icons"
    FILES ${ASSETS}
)
qt_add_qml_module( Qalculator.App
    URI "qalculator.app"
    RESOURCE_PREFIX "/"
    QML_FILES ${QML_SOURCES}
)

target_link_libraries( Qalculator.App PRIVATE Qt6::Gui Qt6::Quick Qalculator.Style )
