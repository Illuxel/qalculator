TEMPLATE = app
TARGET = QML-Calculator

DESTDIR = ../Compiles/QML-Calculator/Debug

QT += core gui qml quick widgets opengl
CONFIG += debug console
CONFIG -= flat

DEFINES += _CONSOLE _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_WIDGETS_LIB QT_QUICK_LIB QT_OPENGL_LIB QT_QMLMODELS_LIB QT_QML_LIB QT_QMLINTEGRATION_LIB
INCLUDEPATH += . \
    ./Build/Debug/moc \
    $(QTDIR)/mkspecs/win32-msvc
DEPENDPATH += .

OBJECTS_DIR += debug
MOC_DIR += Build/$(ConfigurationName)/moc
UI_DIR += .
RCC_DIR += ./Build/Debug/rcc

BACK = $$PWD/src/back
FRONT = $$PWD/src/front

HEADERS += $$BACK/Calculator.h \
    $$BACK/Converter.h \ 
    $$BACK/OperationHistory.h

SOURCES += $$BACK/Calculator.cpp \
    $$BACK/Converter.cpp \
    $$BACK/OperationHistory.cpp \
    $$BACK/main.cpp

RESOURCES += $$FRONT/qml.qrc
