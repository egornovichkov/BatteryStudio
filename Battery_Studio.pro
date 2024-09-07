QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    batinfowidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    batinfowidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/BatteryIcon.png

DISTFILES += \
    fonts/FiraCode.ttf \
    fonts/Inter-Regular.otf \
    fonts/JetBrainsMono-Regular.ttf \
    fonts/Roboto-Medium.ttf \
    fonts/Roboto-Regular.ttf
