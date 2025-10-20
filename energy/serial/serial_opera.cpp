#include "serial_opera.h"

serial_opera::serial_opera(QWidget *parent)
    : QWidget(parent)
{
    init_UI();

    refresh_port_info();

    QObject::connect(refreshButton, &QPushButton::clicked, this, &serial_opera::slot_refresh_ports, Qt::DirectConnection);
    QObject::connect(openCloseButton, &QPushButton::clicked, this, &serial_opera::slot_toggle_port, Qt::DirectConnection);
}

serial_opera::~serial_opera()
{
}

void serial_opera::slot_refresh_ports()
{
    refresh_port_info();
}

void serial_opera::slot_toggle_port()
{

}

void serial_opera::init_UI()
{
    QVBoxLayout* _layout = new QVBoxLayout();

    _group_box = new QGroupBox("串口操作");

    _layout->addWidget(_group_box);

    auto* layout = new QGridLayout(_group_box);

    // 串口号
    layout->addWidget(new QLabel("串口号:"), 0, 0);
    _port_combo = new QComboBox(this);
    layout->addWidget(_port_combo, 0, 1);

    // 波特率
    layout->addWidget(new QLabel("波特率:"), 1, 0);
    _baud_combo = new QComboBox(this);
    _baud_combo->addItems({"9600", "19200", "38400", "57600", "115200"});
    _baud_combo->setCurrentText("9600");
    layout->addWidget(_baud_combo, 1, 1);

    // 校验位
    layout->addWidget(new QLabel("校验位:"), 2, 0);
    _parity_combo = new QComboBox(this);
    _parity_combo->addItems({"无", "奇校验", "偶校验"});
    layout->addWidget(_parity_combo, 2, 1);

    // 数据位
    layout->addWidget(new QLabel("数据位:"), 3, 0);
    _dataBits_combo = new QComboBox(this);
    _dataBits_combo->addItems({"5", "6", "7", "8"});
    _dataBits_combo->setCurrentText("8");
    layout->addWidget(_dataBits_combo, 3, 1);

    // 停止位
    layout->addWidget(new QLabel("停止位:"), 4, 0);
    _stopBits_combo = new QComboBox(this);
    _stopBits_combo->addItems({"1", "1.5", "2"});
    layout->addWidget(_stopBits_combo, 4, 1);

    // 流控制
    layout->addWidget(new QLabel("流控制:"), 5, 0);
    _flowControl_combo = new QComboBox(this);
    _flowControl_combo->addItems({"无", "硬件", "软件"});
    layout->addWidget(_flowControl_combo, 5, 1);

    // 打开/关闭按钮
    refreshButton = new QPushButton("刷新串口", this);
    layout->addWidget(refreshButton, 6, 0);
    openCloseButton = new QPushButton("打开串口", this);
    layout->addWidget(openCloseButton, 6, 1);

    setLayout(_layout);
}

void serial_opera::refresh_port_info()
{
    _port_combo->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : ports){
        // qDebug() << "availavle port is" << info.portName();
        _port_combo->addItem(info.portName());
    }
}
