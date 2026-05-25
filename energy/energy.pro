QT += core gui
QT += serialport sql charts svgwidgets widgets printsupport

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    charts/ac_chart.cpp \
    charts/ac_i_six_chart.cpp \
    charts/ac_i_u_twelve_chart.cpp \
    charts/ac_u_six_chart.cpp \
    charts/dc_chart.cpp \
    charts/phasewave_chart.cpp \
    global/led.cpp \
    main.cpp \
    mainwindow.cpp \
    process/process_1.cpp \
    process/process_2.cpp \
    process/process_24.cpp \
    process/process_25.cpp \
    process/process_26.cpp \
    process/process_3.cpp \
    qcustomplot.cpp \
    serial/serial_port.cpp \
    serial/serial_ui.cpp \
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
    test/test_factory.cpp \
    ui/chooser.cpp \
    ui/ui_001.cpp \
    ui/ui_002.cpp \
    ui/ui_003.cpp \
    ui/ui_004.cpp \
    ui/ui_005.cpp \
    ui/ui_006.cpp \
    ui/ui_007.cpp \
    ui/ui_008.cpp \
    ui/ui_009.cpp \
    ui/ui_010.cpp \
    ui/ui_011.cpp \
    ui/ui_012.cpp \
    ui/ui_013.cpp \
    ui/ui_014.cpp \
    ui/ui_015.cpp \
    ui/ui_016.cpp \
    ui/ui_017.cpp \
    ui/ui_018.cpp \
    ui/ui_019.cpp \
    ui/ui_020.cpp \
    ui/ui_021.cpp \
    ui/ui_022.cpp \
    ui/ui_023.cpp \
    ui/ui_024.cpp \
    ui/ui_025.cpp \
    ui/ui_026.cpp \
    ui/ui_027.cpp

HEADERS += \
    charts/ac_chart.h \
    charts/ac_i_six_chart.h \
    charts/ac_i_u_twelve_chart.h \
    charts/ac_u_six_chart.h \
    charts/dc_chart.h \
    charts/phasewave_chart.h \
    global/index.h \
    global/led.h \
    global/utils.h \
    mainwindow.h \
    process/process.h \
    process/process_1.h \
    process/process_2.h \
    process/process_24.h \
    process/process_25.h \
    process/process_26.h \
    process/process_3.h \
    qcustomplot.h \
    serial/serial_port.h \
    serial/serial_ui.h \
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
    test/test_factory.h \
    ui/chooser.h \
    ui/ui_001.h \
    ui/ui_002.h \
    ui/ui_003.h \
    ui/ui_004.h \
    ui/ui_005.h \
    ui/ui_006.h \
    ui/ui_007.h \
    ui/ui_008.h \
    ui/ui_009.h \
    ui/ui_010.h \
    ui/ui_011.h \
    ui/ui_012.h \
    ui/ui_013.h \
    ui/ui_014.h \
    ui/ui_015.h \
    ui/ui_016.h \
    ui/ui_017.h \
    ui/ui_018.h \
    ui/ui_019.h \
    ui/ui_020.h \
    ui/ui_021.h \
    ui/ui_022.h \
    ui/ui_023.h \
    ui/ui_024.h \
    ui/ui_025.h \
    ui/ui_026.h \
    ui/ui_027.h

FORMS += \
    mainwindow.ui \
    serial/serial_ui.ui \
    ui/chooser.ui \
    ui/ui_001.ui \
    ui/ui_002.ui \
    ui/ui_003.ui \
    ui/ui_004.ui \
    ui/ui_005.ui \
    ui/ui_006.ui \
    ui/ui_007.ui \
    ui/ui_008.ui \
    ui/ui_009.ui \
    ui/ui_010.ui \
    ui/ui_011.ui \
    ui/ui_012.ui \
    ui/ui_013.ui \
    ui/ui_014.ui \
    ui/ui_015.ui \
    ui/ui_016.ui \
    ui/ui_017.ui \
    ui/ui_018.ui \
    ui/ui_019.ui \
    ui/ui_020.ui \
    ui/ui_021.ui \
    ui/ui_022.ui \
    ui/ui_023.ui \
    ui/ui_024.ui \
    ui/ui_025.ui \
    ui/ui_026.ui \
    ui/ui_027.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc \
    .\qdarkstyle\light\lightstyle.qrc \
    .\qdarkstyle\dark\darkstyle.qrc
