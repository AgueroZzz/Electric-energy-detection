QT += core gui
QT += serialport sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global/component.cpp \
    global/tools.cpp \
    main.cpp \
    mainwindow.cpp \
    serial/serial_opera.cpp \
    serial/serial_port.cpp \
    sql/sql.cpp \
    test/test.cpp \
    test/test_01.cpp \
    test/test_02.cpp \
    test/test_03.cpp \
    test/test_04.cpp \
    test/test_05.cpp \
    test/test_06.cpp \
    test/test_07.cpp \
    test/test_08.cpp \
    test/test_09.cpp \
    test/test_10.cpp \
    test/test_11.cpp \
    test/test_12.cpp \
    test/test_13.cpp \
    test/test_14.cpp \
    test/test_15.cpp \
    test/test_16.cpp \
    test/test_17.cpp \
    test/test_18.cpp \
    test/test_19.cpp \
    test/test_20.cpp \
    test/test_21.cpp \
    test/test_22.cpp \
    test/test_23.cpp \
    test/test_24.cpp \
    test/test_25.cpp \
    test/test_26.cpp \
    test/test_27.cpp \
    test/test_choose.cpp \
    ui/test01/ui_001.cpp \
    ui/test01/ui_charts.cpp \
    ui/test02/ui_002.cpp \
    ui/test02/ui_charts_002.cpp \
    ui/test02/ui_table_002.cpp \
    ui/test03/ui_003.cpp \
    ui/test04/ui_004.cpp \
    ui/test05/ui_005.cpp \
    ui/test06/ui_006.cpp \
    ui/test07/ui_007.cpp \
    ui/test08/ui_008.cpp \
    ui/test09/ui_009.cpp \
    ui/test10/ui_010.cpp \
    ui/test11/ui_011.cpp \
    ui/test12/ui_012.cpp \
    ui/test13/ui_013.cpp \
    ui/test14/ui_014.cpp \
    ui/test15/ui_015.cpp \
    ui/test16/ui_016.cpp \
    ui/test17/ui_017.cpp \
    ui/test18/ui_018.cpp \
    ui/test19/ui_019.cpp \
    ui/test20/ui_020.cpp \
    ui/test21/ui_021.cpp \
    ui/test22/ui_022.cpp \
    ui/test23/ui_023.cpp \
    ui/test24/ui_024.cpp \
    ui/test25/ui_025.cpp \
    ui/test26/ui_026.cpp \
    ui/test27/ui_027.cpp

HEADERS += \
    global/component.h \
    global/tools.h \
    mainwindow.h \
    serial/serial_opera.h \
    serial/serial_port.h \
    sql/sql.h \
    test/test.h \
    test/test_01.h \
    test/test_02.h \
    test/test_03.h \
    test/test_04.h \
    test/test_05.h \
    test/test_06.h \
    test/test_07.h \
    test/test_08.h \
    test/test_09.h \
    test/test_10.h \
    test/test_11.h \
    test/test_12.h \
    test/test_13.h \
    test/test_14.h \
    test/test_15.h \
    test/test_16.h \
    test/test_17.h \
    test/test_18.h \
    test/test_19.h \
    test/test_20.h \
    test/test_21.h \
    test/test_22.h \
    test/test_23.h \
    test/test_24.h \
    test/test_25.h \
    test/test_26.h \
    test/test_27.h \
    test/test_choose.h \
    test/test_factory.h \
    ui/test01/ui_001.h \
    ui/test01/ui_charts.h \
    ui/test02/ui_002.h \
    ui/test02/ui_charts_002.h \
    ui/test02/ui_table_002.h \
    ui/test03/ui_003.h \
    ui/test04/ui_004.h \
    ui/test05/ui_005.h \
    ui/test06/ui_006.h \
    ui/test07/ui_007.h \
    ui/test08/ui_008.h \
    ui/test09/ui_009.h \
    ui/test10/ui_010.h \
    ui/test11/ui_011.h \
    ui/test12/ui_012.h \
    ui/test13/ui_013.h \
    ui/test14/ui_014.h \
    ui/test15/ui_015.h \
    ui/test16/ui_016.h \
    ui/test17/ui_017.h \
    ui/test18/ui_018.h \
    ui/test19/ui_019.h \
    ui/test20/ui_020.h \
    ui/test21/ui_021.h \
    ui/test22/ui_022.h \
    ui/test23/ui_023.h \
    ui/test24/ui_024.h \
    ui/test25/ui_025.h \
    ui/test26/ui_026.h \
    ui/test27/ui_027.h

FORMS += \
    mainwindow.ui \
    serial/serial_opera.ui \
    test/test_choose.ui \
    ui/test01/ui_001.ui \
    ui/test01/ui_charts.ui \
    ui/test02/ui_002.ui \
    ui/test02/ui_table_002.ui \
    ui/test03/ui_003.ui \
    ui/test04/ui_004.ui \
    ui/test05/ui_005.ui \
    ui/test06/ui_006.ui \
    ui/test07/ui_007.ui \
    ui/test08/ui_008.ui \
    ui/test09/ui_009.ui \
    ui/test10/ui_010.ui \
    ui/test11/ui_011.ui \
    ui/test12/ui_012.ui \
    ui/test13/ui_013.ui \
    ui/test14/ui_014.ui \
    ui/test15/ui_015.ui \
    ui/test16/ui_016.ui \
    ui/test17/ui_017.ui \
    ui/test18/ui_018.ui \
    ui/test19/ui_019.ui \
    ui/test20/ui_020.ui \
    ui/test21/ui_021.ui \
    ui/test22/ui_022.ui \
    ui/test23/ui_023.ui \
    ui/test24/ui_024.ui \
    ui/test25/ui_025.ui \
    ui/test26/ui_026.ui \
    ui/test27/ui_027.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
