QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindow/mainwindow.cpp \
    WidgetFrame/src/windowbar.cpp \
    WidgetFrame/src/windowbutton.cpp \
    batchargeimg.cpp \
    flag.cpp \
    ledimg.cpp \
    main.cpp \
    warninggroup.cpp \
    warning.cpp

HEADERS += \
    MainWindow/mainwindow.h \
    WidgetFrame/src/windowbar.h \
    WidgetFrame/src/windowbar_p.h \
    WidgetFrame/src/windowbutton.h \
    WidgetFrame/src/windowbutton_p.h \
    batchargeimg.h \
    flag.h \
    ledimg.h \
    warninggroup.h \
    warning.h

FORMS += \
    MainWindow/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    WidgetFrame/resources/shared.qrc \
    images/BatteryIcon.png \
    images/CloseIcon.png \
    images/defaultsizeicon.png \
    images/maximizeicon.png \
    images/minimizeicon.png

DISTFILES += \
    WidgetFrame/resources/app/example.icns \
    WidgetFrame/resources/app/example.ico \
    WidgetFrame/resources/app/example.png \
    WidgetFrame/resources/window-bar/close.svg \
    WidgetFrame/resources/window-bar/fullscreen.svg \
    WidgetFrame/resources/window-bar/maximize.svg \
    WidgetFrame/resources/window-bar/minimize.svg \
    WidgetFrame/resources/window-bar/more-line.svg \
    WidgetFrame/resources/window-bar/restore.svg \
    fonts/FiraCode.ttf \
    fonts/Inter-Regular.otf \
    fonts/JetBrainsMono-Regular.ttf \
    fonts/Roboto-Medium.ttf \
    fonts/Roboto-Regular.ttf

include("/path/install/share/QWindowKit/qmake/QWKWidgets.pri")
