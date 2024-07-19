QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
           GL_SILENCE_DEPRECATION # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/Parser/parser.cc \
    ../Model/center_model.cc \
    ../Model/transform.cc \
    ../Model/facade_model.cc \
    ../Controller/facade_controller.cc \
    gif.cc \
    main.cc \
    mainwindow.cc \
    glwidget.cc

HEADERS += \
    ../Model/Parser/parser.h \
    ../Model/center_model.h \
    ../Model/transform.h \
    ../Model/facade_model.h \
    ../Controller/facade_controller.h \
    gif.h \
    mainwindow.h \
    glwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
