#include "serial_port.h"

serial_port::serial_port(QStringList deploy, QObject *parent)
    : QObject{parent}, _deploy(deploy)
{
    this->moveToThread(&_thread);
    serial_status = false;
    QObject::connect(&_thread, &QThread::started, this, &serial_port::slot_thread_start, Qt::DirectConnection);
    QObject::connect(&_thread, &QThread::finished, this, &serial_port::slot_thread_stop, Qt::DirectConnection);
}

void serial_port::slot_thread_start()
{
    _port = new QSerialPort();
    _port->setPortName(_deploy[s_name]);
    _port->setBaudRate(_deploy[s_baudrate].toUInt());
    _port->setParity(static_cast<QSerialPort::Parity>(_deploy[s_parity].toUInt()));
    _port->setDataBits(static_cast<QSerialPort::DataBits>(_deploy[s_databits].toUInt()));
    _port->setStopBits(static_cast<QSerialPort::StopBits>(_deploy[s_stopbits].toUInt()));
    _port->setFlowControl(static_cast<QSerialPort::FlowControl>(_deploy[s_flowcontrol].toUInt()));

    QObject::connect(_port, &QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error){
        serial_status = false;
        if (error == QSerialPort::ResourceError) {
            qCritical() << "严重错误:" << _port->errorString();
        } else if (error != QSerialPort::NoError) {
            qWarning() << "串口错误:" << _port->errorString();
        }
    });

    if(!_port->open(QIODeviceBase::ReadWrite)){
        serial_status = false;
    }
    serial_status = true;
}

void serial_port::slot_thread_stop()
{
    if(_port->isOpen()){
        _port->close();
        _port->deleteLater();
        _port = nullptr;
    }
    serial_status = false;
}

void serial_port::slot_send_msg_to_serial(const QByteArray *msg)
{

}

void serial_port::slot_recv_msg_from_serial()
{

}
