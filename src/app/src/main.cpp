#include "Calculator.hpp"
#include "Converter.hpp"
#include "ConverterHandler.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include <QIcon>

qint32 main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setApplicationVersion("1.0.0");
    QGuiApplication::setApplicationName("Qalculator");
    QGuiApplication::setApplicationDisplayName("Qalculator");
    QGuiApplication::setWindowIcon(QIcon(":/icons/icon_calculator.png"));

    std::unique_ptr<History>          history(std::make_unique<History>());
    std::unique_ptr<ConverterHandler> cnvtHandler(std::make_unique<ConverterHandler>());

    qmlRegisterSingletonInstance("qalculator.History", 1, 0, "History", history.get());
    qmlRegisterSingletonInstance("qalculator.ConverterHandler", 1, 0, "ConverterHandler", cnvtHandler.get());

    qmlRegisterType<Standart>("qalculator.Standart", 1, 0, "Standart");
    qmlRegisterType<Converter>("qalculator.Converter", 1, 0, "Converter");

    QQmlApplicationEngine engine(":/qalculator/app/qml/MainWindow.qml");

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
