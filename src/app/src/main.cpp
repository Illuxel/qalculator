#include "History.hpp"

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

    QGuiApplication::setApplicationName("Qalculator");
    QGuiApplication::setApplicationDisplayName("Qalculator");
    QGuiApplication::setApplicationVersion("1.0.0");

    QGuiApplication::setWindowIcon(QIcon(":/icons/icon_calculator.png"));

    std::unique_ptr<ConverterHandler> cnvtHandler(std::make_unique<ConverterHandler>());

    qmlRegisterSingletonInstance("qalculator.ConverterHandler", 1, 0, "ConverterHandler", cnvtHandler.get());

    qmlRegisterType<History>("qalculator.History", 1, 0, "History");
    qmlRegisterType<Standart>("qalculator.Calculator", 1, 0, "Calculator");
    qmlRegisterType<Converter>("qalculator.Converter", 1, 0, "Converter");

    QQmlApplicationEngine engine(":/qalculator/app/qml/MainWindow.qml");

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
