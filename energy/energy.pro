QT += core gui
QT += serialport sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global/component.cpp \
    main.cpp \
    mainwindow.cpp \
    serial/serial_opera.cpp \
    serial/serial_port.cpp \
    sql/sql.cpp \
    test/test.cpp \
    test/test_01.cpp \
    test/test_02.cpp \
    test/test_choose.cpp \
    ui/test01/ui_001.cpp \
    ui/test01/ui_charts.cpp \
    ui/test02/ui_002.cpp \
    ui/test03/ui_003.cpp

HEADERS += \
    global/component.h \
    mainwindow.h \
    serial/serial_opera.h \
    serial/serial_port.h \
    sql/sql.h \
    test/test.h \
    test/test_01.h \
    test/test_02.h \
    test/test_choose.h \
    ui/test01/ui_001.h \
    ui/test01/ui_charts.h \
    ui/test02/ui_002.h \
    ui/test03/ui_003.h

FORMS += \
    mainwindow.ui \
    serial/serial_opera.ui \
    test/test_choose.ui \
    ui/test01/ui_001.ui \
    ui/test01/ui_charts.ui \
    ui/test02/ui_002.ui \
    ui/test03/ui_003.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
