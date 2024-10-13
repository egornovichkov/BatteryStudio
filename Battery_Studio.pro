QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Models/CellsDataModel/cellstableproxymodel.cpp \
    src/Views/CellsDataView/cellstableviewwidget.cpp \
    src/Views/CellsDataView/cellsviewdelegate.cpp \
    src/main.cpp \
    src/Models/CellsDataModel/cellsdatamodel.cpp \
    src/BatChargeImg/batchargeimg.cpp \
    src/Flag/flag.cpp \
    src/Flag/ledimg.cpp \
    src/MainWindow/mainwindow.cpp \
    src/Warning/warning.cpp \
    src/Warning/warninggroup.cpp \
    src/WidgetFrame/src/windowbar.cpp \
    src/WidgetFrame/src/windowbutton.cpp

HEADERS += \
    src/BatChargeImg/batchargeimg.h \
    src/Flag/flag.h \
    src/Flag/ledimg.h \
    src/MainWindow/mainwindow.h \
    src/Models/CellsDataModel/cellsdatamodel.h \
    src/Models/CellsDataModel/cellstableproxymodel.h \
    src/Views/CellsDataView/cellstableviewwidget.h \
    src/Views/CellsDataView/cellsviewdelegate.h \
    src/Warning/warning.h \
    src/Warning/warninggroup.h \
    src/WidgetFrame/src/windowbar.h \
    src/WidgetFrame/src/windowbar_p.h \
    src/WidgetFrame/src/windowbutton.h \
    src/WidgetFrame/src/windowbutton_p.h \
    src/bstunamespace.h

FORMS += \
    src/MainWindow/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/CloseIcon.png \
    images/defaultsizeicon.png \
    images/maximizeicon.png \
    images/minimizeicon.png \
    src/MainWindow/mainwindow.qrc \
    src/WidgetFrame/resources/shared.qrc \
    src/MainWindow/TitleBar.qss \
    src/WidgetFrame/resources/app/BatteryIcon.png \
    src/WidgetFrame/resources/app/example.icns \
    src/WidgetFrame/resources/app/example.ico \
    src/WidgetFrame/resources/app/example.png \
    src/WidgetFrame/resources/window-bar/close.svg \
    src/WidgetFrame/resources/window-bar/fullscreen.svg \
    src/WidgetFrame/resources/window-bar/maximize.svg \
    src/WidgetFrame/resources/window-bar/minimize.svg \
    src/WidgetFrame/resources/window-bar/more-line.svg \
    src/WidgetFrame/resources/window-bar/restore.svg

DISTFILES += \
    fonts/FiraCode.ttf \
    fonts/Inter-Regular.otf \
    fonts/JetBrainsMono-Regular.ttf \
    fonts/Roboto-Medium.ttf \
    fonts/Roboto-Regular.ttf \

include("/path/install/share/QWindowKit/qmake/QWKWidgets.pri")
