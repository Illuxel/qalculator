#include "Calculator.hpp"
#include "Converter.hpp"
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon("qrc:/assets/calculator.png"));

    // history is static object
    QScopedPointer<History>          history(new History());
    QScopedPointer<ConverterHandler> cnvtHandler(new ConverterHandler());

    qmlRegisterSingletonInstance("Calculator.History", 1, 0, "History", history.get());
    qmlRegisterSingletonInstance("Calculator.ConverterHandler", 1, 0, "ConverterHandler", cnvtHandler.get());

    qmlRegisterType<Standart>("Calculator.Standart", 1, 0, "Standart");
    qmlRegisterType<Converter>("Calculator.Converter", 1, 0, "Converter");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/qml/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
