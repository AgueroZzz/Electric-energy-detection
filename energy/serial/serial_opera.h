#ifndef SERIAL_OPERA_H
#define SERIAL_OPERA_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSerialPortInfo>
#include <QGroupBox>

#include "serial/serial_port.h"

namespace Ui {
class serial_opera;
}

class serial_opera : public QWidget
{
    Q_OBJECT

public:
    explicit serial_opera(QWidget *parent = nullptr);
    ~serial_opera();

private slots:
    void slot_refresh_ports();      // 刷新串口
    void slot_toggle_port();        // 打开/关闭串口

private:
    serial_port* _serial = nullptr;

    QGroupBox* _group_box;

    QComboBox* _port_combo;
    QComboBox* _baud_combo;
    QComboBox* _parity_combo;
    QComboBox* _dataBits_combo;
    QComboBox* _stopBits_combo;
    QComboBox* _flowControl_combo;

    QPushButton *refreshButton;
    QPushButton *openCloseButton;

    void init_UI();

    void refresh_port_info();
};

#endif // SERIAL_OPERA_H
