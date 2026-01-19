#include "serial_ui.h"
#include "ui_serial_ui.h"
#include "serial/serial_port.h"

extern serial_port* _serial;

serial_ui::serial_ui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serial_ui)
{
    ui->setupUi(this);
    setWindowTitle("串口操作");
    QObject::connect(ui->btn_refresh, &QPushButton::clicked, this, &serial_ui::slot_refresh_port);
    QObject::connect(this, &serial_ui::sig_serial_opera, _serial, &serial_port::slot_serial_opera, Qt::QueuedConnection);
    QObject::connect(_serial, &serial_port::sig_serial_status_changed, this, &serial_ui::slot_serial_status_changed, Qt::QueuedConnection);
    QObject::connect(ui->btn_opera_open, &QPushButton::clicked, this, [=](){
        QStringList serial_deploy;
        serial_deploy << ui->cb_serial_name->currentText()
                      << ui->cb_baudrate->currentText()
                      << ui->cb_data->currentText()
                      << QString::number(ui->cb_flow->currentIndex())
                      << index_parity_change(ui->cb_parity->currentText())
                      << index_stop_change(ui->cb_stop->currentText());
        emit sig_serial_opera(index_serial_status::serial_on, serial_deploy);
    });
    QObject::connect(ui->btn_opera_close, &QPushButton::clicked, this, [=](){
        emit sig_serial_opera(index_serial_status::serial_off);
    });

    slot_refresh_port();

    setLed(ui->lb_led);
}

serial_ui::~serial_ui()
{
    delete ui;
}

void serial_ui::setLed(QLabel *label, index_serial_status status, int size)
{
    // 将label中的文字清空
    label->setText("");
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (status) {
    case index_serial_status::serial_off:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case index_serial_status::serial_on:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

void serial_ui::slot_refresh_port()
{
    ui->cb_serial_name->clear();
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        // 可以显示端口名称和描述信息
        QString displayText = port.portName();
        ui->cb_serial_name->addItem(displayText, port.portName());
    }

    // 如果没有找到串口，添加提示项
    if (ports.isEmpty()) {
        ui->cb_serial_name->addItem("No serial ports found");
        ui->cb_serial_name->setEnabled(false);
    } else {
        ui->cb_serial_name->setEnabled(true);
    }
}

void serial_ui::slot_serial_status_changed(index_serial_status status)
{
    setLed(ui->lb_led, status);
}
